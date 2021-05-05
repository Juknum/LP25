#include <stdio.h>

/**
 * Echange de deux pointeurs
 * @param int *a
 * @param int *b
*/
void swap(int *a, int *b)
{
  int c = *a;
  *a = *b;
  *b = c;
}

int main(void)
{
  int a = 1;
  int b = 2;

  printf("a: %d, b: %d\n", a, b);
  swap(&a, &b);
  printf("a: %d, b: %d\n", a, b);

  return 0;
}