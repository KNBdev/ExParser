#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
};

//-----------------------------------------------------------------------------

void
printComplex (
  double complex c
) {

  printf("%f + %f * i", creal(c), cimag(c));
}

//-----------------------------------------------------------------------------

bool
isEqual (
  double complex a,
  double complex b,
  double margin
) {

  return (cabs(a - b) < fabs(margin));
}

//-----------------------------------------------------------------------------

int
main (
  void
) {

  // Test cases are designed for these two fixed values. DO NOT CHANGE!
  double _real = 3.5;
  double complex _complex = 6 + 2.25 * I;

  epVariables *vars = epVariables__create();
  epVariables__add_real(vars, "r", &_real);
  epVariables__add_complex(vars, "c", &_complex);

  unsigned int size = sizeof(testCases) / sizeof(testCases[0]);
  unsigned int error;

  double complex result;
  double complex _result;

  double margin = 1e-5;

  for (unsigned int i = 0; i < size; i++) {

    _result = testCases[i].result;

    printf("----------------\n");
    printf("Current expression: %s\n", testCases[i].string);
    printf("Expected result: ");
    printComplex(_result);
    printf("\n");

    epExpression *expr = epExpression__compile(
      testCases[i].string,
      &error,
      vars
    );

    if (!expr) {
      printf("Error occured during compilation!\n");
      continue;
    }

    result = epExpression__eval_complex(expr);
    epExpression__delete(expr);

    printf("Evaluated result: ");
    printComplex(result);
    printf("\n");

    assert(isEqual(result, _result, margin));
  }

  epVariables__delete(vars);

  return 0;
}