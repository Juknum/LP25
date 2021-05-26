
#include "db_directory.h"
#include <stdbool.h>
#include <dirent.h>

bool check_db_directory(char *name) {
  DIR* d = opendir(name); // dir needs to be in the same folder than the database
  
  if (!d) return false;

  closedir(d);
  return true;
}

void create_db_directory(char *name) {
  mkdir(name, 0755);
}
