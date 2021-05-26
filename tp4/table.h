#ifndef TABLE_H
#define TABLE_H

#define TEXT_LENGTH 150
#define MAX_FIELDS 10
#define BUFFER_SIZE (MAX_FIELDS * TEXT_LENGTH)

#include <stdbool.h>

typedef enum {
  TYPE_INTEGER,
  TYPE_FLOAT,
  TYPE_TEXT
} e_field_type;

typedef struct {
  char col_name[TEXT_LENGTH];
  e_field_type col_type;
} s_field;

typedef struct {
  s_field field_def;
  union {
    double float_value;
    long long int_value;
    char text_value[TEXT_LENGTH];
  } field_value;
} s_field_record;

/**
 * Check if a table already exist
 * @param name
 * @return bool - true if the table already exist
 */
bool table_exists(char* name);

/**
 * Create the table and nested files that refer to this table
 * - name.idx : binary index file (empty at start)
 * - name.def : table definition file, text file
 * - name.data : bin file of the content of the table (empty at start)
 * 
 * @param name of the created table
 * @param fields[]
 * @param fields_count number of fields
 */
void create_table(char* name, s_field fields[], int fields_count);

/**
 * Get the path of file with the given suffix
 * @param table_name
 * @param suffix
 * @return char* - table_name + suffix
 */
char* concat_name(char* table_name, char* suffix);

/**
 * Add given lines to the given table
 * @param table_name
 * @param row[]
 * @param fields_count number of fields
 */
void add_row_to_table(char* table_name, s_field_record row[], int fields_count);

/**
 * Make buffer
 * @param buffer
 * @param table_name
 * @param row[]
 * @param fields_count number of fields
 * @return int - number of byte to write // nombre d'octet à écrire
 */
int format_row(char* buffer, char* table_name, s_field_record row[], int fields_count);

/**
 * Write line in the .data file of the given table
 * @param buffer
 * @param table_name
 * @param size
 * @return int - position at the begining of the line
 */
int write_row(char* buffer, char* table_name, int size);

/**
 * Insert at the given index inside the .idx file of the table
 * @param index position
 * @param table_name
 */
void insert_index(int index, char* table_name);

/**
 * Read the definition file of the given table and tell how many fields there is
 * @param table_name
 * @param fields[]
 * @returns int - number of existing fields inside the database
 */
int get_table_definition(char* table_name, s_field fields[]);

/**
 * Get the length of a line buffer trough the given fields
 * @param fields[]
 * @param fields_count number of fields
 * @return int - buffer
 */
int get_row_length(s_field fields[], int fields_count);

/**
 * Copy the given buffer inside the line of the given table at the offset position
 * @param table_name
 * @param offset
 * @param row length
 * @param buffer
 */
void get_line_buffer(char* table_name, int offset, int row_length, char* buffer);

/**
 * Convert the given buffer into a table of s_fields with each fields_count field are written inside the table of fields
 * @param buffer
 * @param fields
 * @param field_records[]
 * @param fields_count number of fields
 */
void convert_row(char* buffer, s_field fields[], s_field_record field_records[], int fields_count);

/**
 * Get the offset of the given row in the given table
 * @param row_number
 * @param table_name
 * @return int - offset
 */
int get_offset(int row_number, char* table_name);

/**
 * Display a row stored inside the records table (from convert_row)
 * @param field_records
 * @param fields_count number of fields
 */
void display_row(s_field_record field_records[], int fields_count);

/**
 * Exploit index information to display lines one by one
 * @param table_name
 */
void display_all(char* table_name);

/**
 * Get the offset from the line in the .data file of the given table
 * @param table_name
 * @param index
 * @return int - offset
 */
int get_offset_from_index(char* table_name, int index);

/**
 * Replace line at the specified offset with values inside row[]
 * @param table_name
 * @param row[]
 * @param fields_count number of fields
 * @param offset where the table needs to be updated
 */
void update_table(char* table_name, s_field_record row[], int fields_count, int offset);

/**
 * Deletes all files indexing the database (.idx, .def, .data) & remove the directory
 * @param table_name
 */
void drop_table(char *table_name);

#endif