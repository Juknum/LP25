#include <stdio.h>

#define SPACE " "
#define DOTS "*"

int main(int argc, char* argv[]) {
  int s = 4;
  FILE* out = NULL;

  if (argc > 1) sscanf(argv[1], "%d", &s);

  if (argc > 2) out = fopen(argv[2], "w");
  else if (out == NULL) out = stdout;

  for (int n = 1; n <= s; n++) {
    for (int o = 0; o < (s-n); o++) fprintf(out, SPACE);
    fprintf(out, DOTS);
    for (int o = 1; o < (n * 2) - 1; o++) fprintf(out, DOTS);
    fprintf(out, "\n");
  }

  for (int n = s - 1; n > 0; n--) {
    for (int o = 0; o < (s - n); o++) fprintf(out, SPACE);
    fprintf(out, DOTS);
    for (int o = 1; o < (n * 2) - 1; o++) fprintf(out, DOTS);
    fprintf(out, "\n");
  }
}