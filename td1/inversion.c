#include <stdio.h>

/**
 * Echange de valeurs entre deux variables
 */
int main(void)
{
  int a = 1;
  int b = 2;

  printf("a: %d, b: %d\n", a, b);
  
  // inversion des valeurs des variables a et b
  {
    int c = a;
    a = b;
    b = c;
  }

  printf("a: %d, b: %d\n", a, b);

  return 0;
}