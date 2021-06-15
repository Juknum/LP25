#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int opt = 0;

  while ((opt = getopt(argc, argv, "oa:b::")) != -1) {
    switch (opt) {
    case 'o':
      printf("-o.\n");
      break;
    case 'a':
      printf("-a: %s\n", optarg);
      break;
    case 'b':
      if (optind < argc && optind > 0 && *argv[optind] != '-') printf("-b: %s\n", argv[optind]);
      else printf("-b\n");
      break;
    case '?':
      return 1;
    default:
      printf("%d/%c: %s\n", opt, opt, optarg);
      break;
    }
  }

  return 0;
}