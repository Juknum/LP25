#ifndef DB_DIRECTORY_H
#define DB_DIRECTORY_H

#include <stdbool.h>

/**
 * check if the directory exist
 * @param name directory name
 * @return bool - true if the directory already exist
 */
bool check_db_directory(char* name);

/**
 * create a directory with the given name
 * @param name
 */
void create_db_directory(char* name);

#endif