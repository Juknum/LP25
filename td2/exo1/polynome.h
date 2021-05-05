#ifndef _POLYNOME_COMPLEX_H_
#define _POLYNOME_COMPLEX_H_

/**
 * Solve Complex Polynome: ax²+bx+c = 0
 * @param double a given value
 * @param double b ''
 * @param double c ''
 * @param int* x1 returned value
 * @param int* x2 ''
 */
void solvePolynomeComplex(double a, double b, double c, double complex *x1, double complex *x2);

#endif