#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MASK 0x7f
#define BUFFER_SIZE 128

unsigned char read_index = 0;
unsigned char write_index = 0;
char circular_buffer[BUFFER_SIZE];

bool write_char(char c) {
  if (read_index == write_index + 1) return false;

  circular_buffer[write_index] = c;
  write_index = (write_index + 1) & MASK;

  return true;
}

bool read_char(char *c) {
  if (read_index == write_index) return false;

  *c = circular_buffer[read_index];

  switch ((int)c[read_index]) {
  case 96 ... 123:
    printf("%c ", (char)((int)c[read_index] - 32));
    break;
  default:
    printf("%c ", c[read_index]);
    break;
  }

  read_index = (read_index + 1) & MASK;

  return true;
}

int main(int argc, char *argv[]) {
  char c;
  bool noErr = true;
  bool done = false;

  printf("Enter a character, use '*' to stop:\n");
  while (!done && noErr) {
    c = getchar();
    if (c == '*') done = true;
    else noErr = write_char(c);
  }

  printf("Printing the buffer: \n");
  int i = 0;
  noErr = true;
  while (circular_buffer[i] != '\0' && noErr) {
    noErr = read_char(circular_buffer);
    i++;
  }

  return 0;
}