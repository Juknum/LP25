#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Please enter a hex file and a bin file!\n");
    return 1;
  }

  FILE *fhex = fopen(argv[1], "r"); // Open in text mode, for reading
  if (!fhex) return 1;

  FILE *fbin = fopen(argv[2], "wb"); // Open in binary write mode
  if (!fbin) return 1;

  char buffer[BUFFER_SIZE];

  while (!feof(fhex)) {
    fgets(buffer, BUFFER_SIZE, fhex);
    if (buffer[7] == '0' && buffer[8] == '0') {
      char temp[3];
      temp[0] = buffer[1];
      temp[1] = buffer[2];
      temp[2] = '\0';
      int size = (int)strtol(temp, NULL, 16);

      uint8_t *line = (uint8_t *)malloc(sizeof(uint8_t) * (size + 1));

      for (int i = 0; i < size * 2; i += 2) {
        temp[0] = buffer[9 + i];
        temp[1] = buffer[10 + i];
        temp[2] = '\0';
        line[i / 2] = (uint8_t)strtol(temp, NULL, 16);
      }
      line[size] = '\0';

      fwrite(line, size, 1, fbin);

      free(line);
    }
  }

  fclose(fbin);
  fclose(fhex); // Do not forget that to free file handle resources
  return 0;
}