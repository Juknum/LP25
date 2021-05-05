#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (argc <= 1) return 1; // pas d'arguments

  size_t length;

  // validation du premier argument
  if (sscanf(argv[1], "%d", &length) != 1) return 1;

  // create array
  size_t* list = (size_t*)malloc(sizeof(size_t)*length);
  if (list == NULL) return 1;

  for (size_t n = 0; n < length; n++) list[n] = n + 1;
  for (size_t n = 0; n < length; n++) printf("%d: %d | ", n, list[n]);

  free(list);
}