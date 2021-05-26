#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
  char* path = ".";

  if (argc > 1) path = argv[1];
  DIR* dir = opendir(path);

  if (!dir) {
    fprintf(stderr, "Can't open the following directory %s", path);
    return 1;
  }

  struct dirent* entry;
  while ((entry = readdir(dir))) {
    char *type;
    switch (entry->d_type) {
      case DT_BLK:
        type = "block";
        break;
      case DT_CHR:
        type = "char";
        break;
      case DT_DIR:
        type = "dir";
        break;
      case DT_FIFO:
        type = "fifo";
        break;
      case DT_REG:
        type = "file";
        break;
      case DT_LNK:
        type = "link";
        break;
      case DT_SOCK:
        type = "socket";
        break;
      default:
        type = "?";
        break;
    }
    printf("%s\t%s\n", type, entry->d_name);
  }

  closedir(dir);
  
  return 0;
}