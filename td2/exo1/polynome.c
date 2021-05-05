#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h>

#include "polynome.h"

/**
 * Solve Complex Polynome: ax²+bx+c = 0
 * @param double a given value
 * @param double b ''
 * @param double c ''
 * @param int* x1 returned value
 * @param int* x2 ''
 */
void solvePolynomeComplex(double a, double b, double c, double complex *x1, double complex *x2) {
  double delta = (b * b) - 4.0 * (a * c);
  
  if (fabs(a) <= DBL_EPSILON && fabs(b) <= DBL_EPSILON) {
    *x1 = 0;
    *x2 = 0;
  }
  else if (fabs(a) <= DBL_EPSILON) {
    *x1 = *x2 = -(c / b);
  }
  else {
    if (delta == 0) {
      *x1 = *x2 = -b / (2.0 * a);
    }
    else if (delta > 0) {
      *x1 = (double complex)((-b + sqrt(delta)) / (2.0 * a));
      *x2 = (double complex)((-b - sqrt(delta)) / (2.0 * a));
    }
    else {
      double complex i = I / (2.0 * (double complex)a);
      *x1 = (double complex)((-b) / (2.0 * a)) + i;
      *x2 = (double complex)((-b) / (2.0 * a)) - i;
    }
  }
}