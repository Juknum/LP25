#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void recurse(char* parent, char* target);

int main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(stderr, "This command needs 2 parameters\n./my-find <parent dir> <taget name>");
    return 1;
  }

  recurse(argv[1], argv[2]);
}

void recurse(char* parent, char* target) {
  DIR* dir = opendir(parent);
  if (!dir) {
    fprintf(stderr, "Can't open the following directory: %s", parent);
    return;
  }

  struct dirent* entry;
  while ((entry = readdir(dir))) {
    if (entry->d_type == DT_DIR && strcmp("..", entry->d_name) != 0 && strcmp(".", entry->d_name) != 0) {
      char* path = malloc(strlen(parent) + strlen(entry->d_name) + 2);
      if (!path) {
        fprintf(stderr, "Can't allocate %zu bytes of memory!\n", strlen(parent) + strlen(entry->d_name) + 2);
        break;
      }

      path[0] = 0;
      strcat(path, parent);
      strcat(path, "/");
      strcat(path, entry->d_name);
      recurse(path, target);
      free(path);
    }
    else if (strcmp(target, entry->d_name) == 0) {
      printf("%s/%s\n", parent, entry->d_name);
    }
  }

  closedir(dir);

}