#include <complex.h>
#include <stdio.h>

#include "exparser.h"

//-------------------------------------

int main (void) {

  // Declare expression strings.
  const char *string_r = "cosh(r^-3) - sin(5/r)";
  const char *string_c = "exp(i/c)^r / sin(3+4i)";

  // Print expressions.
  printf("Real expression   : %s\n", string_r);
  printf("Complex expression: %s\n\n", string_c);

  // Create variables.
  double r = 5;
  double complex c = 3 - 7 * I;

  // Print varaiables.
  printf("Real variable   : %f\n", r);
  printf("Complex variable: %f + %f * i\n\n", creal(c), cimag(c));

  // Set up variable container.
  epVariables *vars = epVariables__create();

  // Add a real variable.
  epVariables__add_real(vars, "r", &r);

  // Add a complex variable.
  epVariables__add_complex(vars, "c", &c);

  // Set up an integer variable that holds the compilation error code.
  int error;

  // Compile the expressions, use error code and variable container.
  epExpression *expression_r = epExpression__compile(string_r, &error, vars);
  epExpression *expression_c = epExpression__compile(string_c, NULL, vars);

  // After compilation, there is no further use for the variable container.
  epVariables__delete(vars);

  // Check if expressions have been compiled successfully.
  if (!expression_r || !expression_c) {

    printf("Error occured during compilation!\n");
    epExpression__delete(expression_r);
    epExpression__delete(expression_c);

    return 1;
  }

  // Evaluate complex expression.
  double result_r = epExpression__eval_real(expression_r);
  double complex result_c = epExpression__eval_complex(expression_c);

  // Delete expressions.
  epExpression__delete(expression_r);
  epExpression__delete(expression_c);

  // Print results.
  printf("Real expression evaluates to   : %f\n", result_r);
  printf(
    "Complex expression evaluates to: %f + %f * i\n",
    creal(result_c),
    cimag(result_c)
  );

  return 0;
}