#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <float.h>

void printfc(double complex c) {
  if (fabs(cimag(c)) > DBL_EPSILON && cimag(c) > 0) printf("%.2lf +%.2lfi", creal(c), cimag(c));
  else if (fabs(cimag(c)) > DBL_EPSILON && cimag(c) < 0) printf("%.2lf %.2lfi", creal(c), cimag(c));
  else if (fabs(creal(c)) > DBL_EPSILON) printf("%.2lf", creal(c));
  else printf("0.00");
}

int main(int argc, char const *argv[])
{
  if (argc < 4) return 1;

  double a = strtod(argv[1], NULL);
  double b = strtod(argv[2], NULL);
  double c = strtod(argv[3], NULL);

  printf("Solving: %.2lfx^2 + %.2lfx + %.2lf = 0 in C:\n", a, b, c);

  double delta = (b * b) - 4.0 * (a * c);
  double complex solution1;
  double complex solution2;
  int n;

  if (fabs(a) <= DBL_EPSILON && fabs(b) <= DBL_EPSILON)
  {
    n = 0;
  }
  else if (fabs(a) <= DBL_EPSILON)
  {
    n = 1;
    solution1 = -(c / b);
  }
  else
  {
    if (delta == 0)
    {
      n = 1;
      solution1 = -b / (2.0 * a);
    }
    else if (delta > 0)
    {
      n = 2;
      solution1 = (double complex)((-b + sqrt(delta)) / (2.0 * a));
      solution2 = (double complex)((-b - sqrt(delta)) / (2.0 * a));
    }
    else
    {
      n = 2;
      double complex i = I / (2.0 * (double complex)a);
      solution1 = (double complex)((-b) / (2.0 * a)) + i;
      solution2 = (double complex)((-b) / (2.0 * a)) - i;
    }
  }

  switch (n)
  {
  case 0:
    printf("No solution");
    break;
  case 1:
    printf("1 solution:\n");
    printf("x = ");
    printfc(solution1);
    break;
  case 2:
    printf("2 solutions:\n");
    printf("x1 = ");
    printfc(solution1);
    printf("\nx2 = ");
    printfc(solution2);
    break;
  default:
    break;
  }

  return 0;
}
