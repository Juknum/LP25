#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUFFER_SIZE 128

void fprint(FILE* f) {
  wchar_t buffer[BUFFER_SIZE];
  
  while (fgetws(buffer, BUFFER_SIZE, f)) wprintf(L"%ls", buffer);
}

int main(int argc, char* argv[]) {
  
  if (argc > 1) {
    for (size_t n = 1; n < argc; n++) {

      FILE* f = fopen(argv[n], "r");
      if (!f) return 1;

      fprint(f);
      fclose(f);
    }
  }
  else fprint(stdin);

  return 0;
}