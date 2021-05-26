#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define BUFFER_SIZE 256

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "en_US.UTF-8");

  if (argc < 2) {
    fprintf(stderr, "You need to specify the file!");
    return 1;
  }

  FILE* f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "Can't open the file!\n", argv[1]);
    return 1;
  }

  wchar_t buffer[BUFFER_SIZE];
  while (fgetws(buffer, BUFFER_SIZE, f)) {
    wprintf(L"%ls", buffer);
  }

  fclose(f);
  return 0;
}