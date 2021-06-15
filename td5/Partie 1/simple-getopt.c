#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int opt = 0;

  while ((opt = getopt(argc, argv, "oa:")) != -1) {
    switch (opt) {
    case 'o':
      printf("-o.\n");
      break;
    case 'a':
      printf("-a: %s\n", optarg);
      break;
    default:
      printf("%d/%c: %s\n", opt, opt, optarg);
      break;
    }
  }

  return 0;
}