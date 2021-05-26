#include "table.h"
#include "main.h"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

bool table_exists(char* name) {
  char *repo_name = (char *)malloc(sizeof(char) * (strlen(name) + strlen(db_path) + 2));
  strcpy(repo_name, db_path);
  strcat(repo_name, "/");
  strcat(repo_name, name);

  DIR* d = opendir(repo_name);

  if (!d) { 
    free(repo_name);
    return false;
  }

  closedir(d);
  free(repo_name);

  return true;
}

void create_table(char *name, s_field fields[], int fields_count) {
  char *repo_name = (char *)malloc(sizeof(char) * (strlen(name) + strlen(db_path) + 2));
  strcpy(repo_name, db_path);
  strcat(repo_name, "/");
  strcat(repo_name, name);
  
  mkdir(repo_name, 0755);
  
  free(repo_name);

  /* -- */
  char *file_name = concat_name(name, "idx");
  FILE* f1 = fopen(file_name, "w");
  fclose(f1);
  free(file_name);
  /* -- */

  /* -- */
  file_name = concat_name(name, "def");
  FILE* f2 = fopen(file_name, "w");
  int max_it = fields_count > MAX_FIELDS ? MAX_FIELDS : fields_count;
  for (size_t i = 0; i < max_it; i++) fprintf(f2, "%d %s\n", fields[i].col_type, fields[i].col_name);
  fclose(f2);
  free(file_name);
  /* -- */

  /* -- */
  file_name = concat_name(name, "data");
  FILE* f3 = fopen(file_name, "w");
  fclose(f3);
  free(file_name);
  /* -- */
}

char* concat_name(char* table_name, char* suffix) {
  char* file_name = (char*)malloc(sizeof(char)*(strlen(table_name)*2 + strlen(db_path) + strlen(suffix) + 4));

  strcpy(file_name, db_path);
  strcpy(file_name, "/");
  strcpy(file_name, table_name);
  strcpy(file_name, "/");
  strcpy(file_name, table_name);
  strcpy(file_name, ".");
  strcpy(file_name, suffix);

  return file_name;
}

void add_row_to_table(char* table_name, s_field_record row[], int fields_count) {
  char* buffer = malloc(sizeof(char)*MAX_FIELDS*TEXT_LENGTH);
  buffer[0] = '\0';
  insert_index(write_row(buffer, table_name, format_row(buffer, table_name, row, fields_count)), table_name);
  free(buffer);
}

int format_row(char* buffer, char* table_name, s_field_record row[], int fields_count) {
  long sum = 0;
  int length;
  int max_it = fields_count > MAX_FIELDS ? MAX_FIELDS : fields_count;

  for (size_t i = 0; i < max_it; i++) {
    switch(row[i].field_def.col_type) {
      case 0:
        length = sizeof(long);
        memcpy(buffer + sum, &row[i].field_value.int_value, length);
        sum += length;
        break;

      case 1:
        length = sizeof(double);
        memcpy(buffer + sum, &row[i].field_value.float_value, length);
        sum += length;
        break;

      default:
        length = sizeof(char[TEXT_LENGTH]);
        for (size_t j = 0; j < TEXT_LENGTH; j++) {
          if (j < strlen(row[i].field_value.text_value)) memcpy(buffer + sum + j, &row[i].field_value.text_value[j], sizeof(char));
          else memset(buffer + sum + j, 0, 1);
        }
        sum += length;
        break;
    }
  }

  return sum;
}

int write_row(char *buffer, char *table_name, int size) {
  char* file_name = concat_name(table_name, "data");
  FILE* f1 = fopen(file_name, "ab");

  fseek(f1, 0, SEEK_END);
  int res = ftell(f1);

  for (size_t i = 0; i < size; i++) fwrite(&buffer[i], sizeof(char), 1, f1);
  
  fclose(f1);
  free(file_name);

  return res;
}

void insert_index(int index, char* table_name) {
  char buffer[MAX_FIELDS];
  int size = 0;
  int nb_lines = 1;
  char* file_name = concat_name(table_name, "idx");
  FILE* f_idx = fopen(file_name, "ab");

  while (size = fread(buffer, sizeof(char), MAX_FIELDS, f_idx)) {
    for (size_t i = 0; i < size; i++) if (buffer[i] == '\n') nb_lines++;
  }
  
  fwrite(&nb_lines, sizeof(int), 1, f_idx);
  fwrite(&index, sizeof(int), 1, f_idx);
  fwrite("\n", sizeof(char), 1, f_idx);

  fclose(f_idx);
  free(file_name);
}

int get_table_definition(char* table_name, s_field fields[]) {
  char* file_name = concat_name(table_name, "def");
  FILE* f1 = fopen(file_name, "r");

  char buffer[TEXT_LENGTH];
  int tmp;
  int isEOF = 0;
  int i = 0;

  while (isEOF != EOF) {
    isEOF = fscanf(f1, "%d %s\n", &tmp, buffer);
    if (isEOF != EOF) fields[i].col_type = tmp;
    strcpy(fields[i].col_name, buffer);
    i++;
  }

  fclose(f1);
  free(file_name);
  return i;
}

int get_row_length(s_field fields[], int fields_count) {
  int min = fields_count > MAX_FIELDS ? MAX_FIELDS : fields_count;
  int res = 1;

  for (size_t i = 0; i < min; i++) {
    switch(fields[i].col_type) {
      case 0:
        res += sizeof(long);
        break;
      case 1:
        res += sizeof(double);
        break;
      default:
        res += sizeof(char[TEXT_LENGTH]);
        break;
    }
  }

  return res;
}

void get_line_buffer(char* table_name, int offset, int row_length, char* buffer) {
  char* file_name = concat_name(table_name, "data");
  FILE* f1 = fopen(file_name, "rb");

  fseek(f1, offset, SEEK_SET);
  fread(buffer, row_length, 1, f1);

  fclose(f1);
  free(file_name);
}

void convert_row(char* buffer, s_field fields[], s_field_record field_records[], int fields_count) {
  int min = fields_count > MAX_FIELDS ? MAX_FIELDS : fields_count;
  int length;
  int sum = 0;

  for (size_t i = 0; i < min; i++) {
    field_records[i].field_def = fields[i];
    switch (fields[i].col_type) {
      case 0:
        length = sizeof(long);
        memcpy(&field_records[i].field_value.int_value, buffer + sum, length);
        sum += length;
        break;
      case 1:
        length = sizeof(double);
        memcpy(&field_records[i].field_value.float_value, buffer + sum, length);
        sum += length;
        break;
      default:
        printf("%s\n", field_records[i].field_value.text_value);
        break;
    }
  }
}

int get_offset(int row_number, char* table_name) {
  char* file_name = concat_name(table_name, "idx");
  FILE* f_idx = fopen(file_name, "rb");

  int offset = -1;
  int tmp = 0;

  if (row_number > 1) fseek(f_idx, (row_number - 1) * (2 * sizeof(int) + sizeof(char)), SEEK_SET);
  if (fread(&tmp, sizeof(int), 1, f_idx)) fread(&offset, sizeof(int), 1, f_idx);

  fclose(f_idx);
  free(file_name);
  return offset;
}

void display_row(s_field_record field_records[], int fields_count) {
  int min = fields_count > MAX_FIELDS ? MAX_FIELDS : fields_count;
  
  for (size_t i = 0; i < min; i++) {
    printf("%s: \t", field_records[i].field_def.col_name);
    switch (field_records[i].field_def.col_type) {
      case TYPE_INTEGER:
        printf("%lld\n", field_records[i].field_value.int_value);
        break;
      case TYPE_FLOAT:
        printf("%f\n", field_records[i].field_value.float_value);
        break;
      default:
        printf("%s\n", field_records[i].field_value.text_value);
        break;
    }
  }
}

void display_all(char* table_name) {
  s_field read_fields[MAX_FIELDS];
  s_field_record read_records[MAX_FIELDS];

  char line_buffer[BUFFER_SIZE];
  int offset = 0;
  int index = 1;

  int fields_count = get_table_definition(table_name, read_fields);
  int row_length = get_row_length(read_fields, fields_count);

  while ((offset = get_offset(index, table_name)) != -1) {
    printf("Entry n°%d:\n", index);
    get_line_buffer(table_name, offset, row_length, line_buffer);
    convert_row(line_buffer, read_fields, read_records, fields_count);
    display_row(read_records, fields_count);
    index++;
  }
}

int get_offset_from_index(char* table_name, int index) {
  int idx = 0;
  int offset = 0;
  char buffer[1];
  int isEOF;

  char* file_name = concat_name(table_name, "idx");
  FILE* f_idx = fopen(file_name, "rb");

  do {
    isEOF = fread(&idx, sizeof(int), 1, f_idx);
    fread(&offset, sizeof(int), 1, f_idx);
    isEOF = fread(buffer, sizeof(char), 1, f_idx);
  } while (idx < index && isEOF != 0);

  fclose(f_idx);
  free(file_name);
  return offset;
}

void update_table(char* table_name, s_field_record row[], int fields_count, int offset) {
  char* buffer = malloc(sizeof(char) * MAX_FIELDS * TEXT_LENGTH);
  char* file_name = concat_name(table_name, "data");

  FILE *f_data = fopen(file_name, "rb+");
  int size_line = 0;

  size_line = format_row(buffer, table_name, row, fields_count);
  fseek(f_data, offset, SEEK_SET);

  for (size_t i = 0; i < size_line; i++) fwrite(&buffer[i], sizeof(char), 1, f_data);

  fclose(f_data);
  free(file_name);
  free(buffer);
}

void drop_table(char *table_name) {
  char* file_name = concat_name(table_name, "idx");
  remove(file_name);
  free(file_name);

  file_name = concat_name(table_name, "def");
  remove(file_name);
  free(file_name);

  file_name = concat_name(table_name, "data");
  remove(file_name);
  free(file_name);

  file_name = (char*)realloc(file_name, sizeof(char) * strlen(table_name) + strlen(db_path) + 2);
  strcpy(file_name, db_path);
  strcat(file_name, "/");
  strcat(file_name, table_name);
  rmdir(file_name);

  free(file_name);
}