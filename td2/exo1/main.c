#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h>

#include "polynome.h"

int main(int argc, char const *argv[]) {
  double complex x1 = 0;
  double complex x2 = 0;

  solvePolynomeComplex(strtod(argv[1], NULL), strtod(argv[2], NULL), strtod(argv[3], NULL), &x1, &x2);

  printf("x1 = %.2lf + %.2lfi\n", creal(x1), cimag(x1));
  printf("x2 = %.2lf + %.2lfi\n", creal(x2), cimag(x2));
  return 0;
}