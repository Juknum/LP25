#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    system("ls -a");
    return 0;
  }

  char *cmd = malloc(sizeof(char)*(strlen(argv[1]) + 6));
  cmd[0] = 0;

  strcat(cmd, "ls -a \"");
  strcat(cmd, argv[1]);
  strcat(cmd, "\"");
  system(cmd);

  free(cmd);

  return 0;
}