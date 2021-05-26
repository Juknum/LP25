
#include "main.h"
#include "db_directory.h"
#include "table.h"

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/**
 * main function
 * @param {char*} argv[] args list
 * @param {int} argc args length
 */
int main(int argc, char* argv[]) {
  /* PARTIE 1 */
  if (argc < 2) return 1;
  if (!check_db_directory(argv[1])) create_db_directory(argv[1]);
  /* -------- */

  db_path = (char*)malloc(sizeof(char)*strlen(argv[1]));
  strcpy(db_path, argv[1]);

  /* PARTIE 2 */
  s_field fields[MAX_FIELDS] = {
    { .col_name = "id",    .col_type = TYPE_INTEGER },
    { .col_name = "label", .col_type = TYPE_TEXT }
  };

  char table_name[TEXT_LENGTH] = "my_table";

  if (!table_exists(table_name)) create_table(table_name, fields, 2);
  /* -------- */

  /* PARTIE 3 */
  s_field_record field_records[MAX_FIELDS] = {
    {
      .field_def = { .col_name = "id", .col_type = TYPE_INTEGER },
      .field_value.int_value = 1
    },
    {
      .field_def = { .col_name = "label", .col_type = TYPE_TEXT },
      .field_value.text_value = "Hello World"
    }
  };

  add_row_to_table(table_name, field_records, 2);
  /* -------- */

  /* PARTIE 4 */
  s_field read_fields[MAX_FIELDS];
  s_field_record read_records[MAX_FIELDS];
  char line_buffer[BUFFER_SIZE];

  int fields_count = get_table_definition(table_name, read_fields);
  int row_length = get_row_length(read_fields, fields_count);

  get_line_buffer(table_name, 0, row_length, line_buffer);
  convert_row(line_buffer, read_fields, read_records, fields_count);
  display_row(read_records, fields_count);

  display_all(table_name);
  /* -------- */

  /* PARTIE 5 */
  s_field_record new_row[MAX_FIELDS] = {
    {
      .field_def = { .col_name = "id", .col_type = TYPE_INTEGER },
      .field_value.int_value = 2
    },
    {
      .field_def = { .col_name = "label", .col_type = TYPE_TEXT },
      .field_value.text_value = "Hello World - Modified"
    }
  };

  int row_offset = get_offset_from_index(table_name, 1);
  update_table(table_name, new_row, 2, row_offset);
  display_all(table_name);
  /* -------- */

  /* PARTIE 6 */
  drop_table(table_name);
  /* -------- */

  return 0;
}