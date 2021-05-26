#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

uint16_t bsd_checksum(uint8_t byte, uint16_t current_checksum) {
  uint16_t checksum = current_checksum;
  checksum = (checksum >> 1) + ((checksum & 1) << 15);
  checksum += byte;
  return checksum;
}

int main(int argc, char* argv[]) {
  if (argc < 2) return 1;

  FILE* f = fopen(argv[1], "rb");
  if (!f) return 1;

  uint16_t checksum = 0;

  int x = 0;
  while ((x = fgetc(f)) != EOF) checksum = bsd_checksum((uint8_t)x, checksum);
  
  printf("%" PRIx16 "\n", checksum);
}