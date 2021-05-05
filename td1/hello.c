#include <stdio.h>

/**
 * Affiche "Hello <param1>"
 */
int main(int argc, char const *argv[])
{
  if (argc != 2)
    return 1;

  printf("Hello, %s!\n", argv[1]);
  return 0;
}