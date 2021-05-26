#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
  char *path = ".";

  if (argc > 1) 
    path = argv[1];
  DIR *dir = opendir(path);

  if (!dir) {
    fprintf(stderr, "Can't open the following directory %s", path);
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir))) {
    struct stat file_stat;
    char *filename = malloc(strlen(path) + strlen(entry->d_name) + 2);
    filename[0] = 0;

    strcat(filename, path);
    strcat(filename, "/");
    strcat(filename, entry->d_name);

    if (stat(filename, &file_stat)) {
      fprintf(stderr, "Can't stat %s\n", filename);
      return 1;
    }

    free(filename);

    printf("%s\t", entry->d_name);

    size_t size = file_stat.st_size;
    printf("%zu", size);

    if (size >= 1 << 30)
      printf("\t%2f Gio", (float)size / (1 << 30));
    else if (size >= (1 << 20))
      printf("\t%.2f Mio", (float)size / (1 << 20));
    else if (size >= (1 << 10))
      printf("\t%.2f Kio", (float)size / (1 << 10));

    if (size >= 1e9)
      printf("\t%.2f Go", (float)size / 1e9);
    if (size >= 1e6)
      printf("\t%.2f Mo", (float)size / 1e6);
    if (size >= 1e3)
      printf("\t%.2f Ko", (float)size / 1e3);

    printf("\n");
  }

  closedir(dir);
}