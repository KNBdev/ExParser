#include <complex.h>
#include <stddef.h>
#include <stdio.h>

#include "exparser.h"

//-----------------------------------------------------------------------------

const struct {
  const char *string;
  const double complex result;
} testCases[] = {

  {"2+3", 5},
  {"-i^sinh(1/c)/-r^2", 0.086703 + 0.020301 * I},
  {"1e-6*10^12", 1e+6},
  {"-i *- log(r/c)^9*i", 0.004464 - 0.041803 * I},
  {"-i *- logJ(r/c)^9*i", 0.004464 - 0.041803 * I},
  {"exp(24)+2*/3", 26489122135.84347},
  {"log exp 1", 1},
  {"log (exp 1)", 1},
  {"sin cos tan 4", 0.390649},
  {"4^3^2", 262144},
  {"]c", 6 + 2.25 * I},
  {"c", 6 + 2.25 * I},
  {"2", 2},
  {"3 - 4", -1.},
  {"3 + 4", 7.},
  {"2 == 3", 0},
  {"4+3i ", 4 + 3 * I},
  {"4+1i ^ 3+0i", 4 - 1 * I},
  {"3+4i != 0", 1},
  {"3+4i == 0+2i", 0},
  {"3+4i == 0", 0},
  {"0 | 2 & (0 | 4i) | 2^0", 1},
  {"2 & 0 | 4", 1},
  {"3 & 12", 1},
};

//-----------------------------------------------------------------------------

void
printComplex (
  double complex c
) {

  printf("%f + %f * i", creal(c), cimag(c));
}

//-------------------------------------

void
printBlanks (
  unsigned int n
) {

  for (unsigned int i = 0; i < n; i++) {
    printf(" ");
  }
}

//-----------------------------------------------------------------------------

int
main (
  void
) {

  // Test cases are designed for these two fixed values.
  double _real = 3.5;
  double complex _complex = 6 + 2.25 * I;

  epVariables *vars = epVariables__create();
  epVariables__add_real(vars, "r", &_real);
  epVariables__add_complex(vars, "c", &_complex);

  unsigned int size = sizeof(testCases) / sizeof(testCases[0]);
  int error;

  epExpression *expr;

  //---------------------------------------------------------------------------

  for (unsigned int i = 0; i < size; i++) {

    char const *s = testCases[i].string;

    printf("---------------------------------------\n");
    printf("%s\n", s);

    expr = epExpression__compile(s, &error, vars);

    if (expr) {

      double complex result = epExpression__eval_complex(expr);

      printf("Calculated result: ");
      printComplex(result);
      printf("\n");

      printf("Expected result  : ");
      printComplex(testCases[i].result);
      printf("\n");

    } else {

      printBlanks((error >= 0) ? error : 0);
      printf("^\nError near here, error code: %d\n", error);
    }

    epExpression__delete(expr);
  }

  //---------------------------------------------------------------------------

  epVariables__delete(vars);

  return 0;
}