#include <stddef.h>
#include <stdio.h>

#include "exparser.h"

//-----------------------------------------------------------------------------

int main (void) {

  // Expression to evaluate.
  const char *expression = "x^2 - sin(x)";

  // Print expression.
  printf("%s\n", expression);

  // Real variables to use during evaluation.
  double old = 4;
  double new = 7;

  // Print variables.
  printf("Old value: %f\n", old);
  printf("New value: %f\n", new);

  // Variables container.
  epVariables *vars = epVariables__create();
  epVariables__add_real(vars, "x", &old);

  // Compilation process.
  epExpression *expr_original = epExpression__compile(expression, NULL, vars);

  // Delete variables container after compilation.
  epVariables__delete(vars);

  // Copy compiled expression without recompilation.
  epExpression *expr_copy = epExpression__duplicate(expr_original);

  // Check for errors.
  if (expr_original) {

    // Assign new variable to copy.
    epExpression__replace_real_variable(expr_copy, &old, &new);

    // Get results from evaluation.
    double result_original = epExpression__eval_real(expr_original);
    double result_copy = epExpression__eval_real(expr_copy);

    // Print results.
    printf("Result for old value: %f\n", result_original);
    printf("Result for new value: %f\n", result_copy);
  }

  // Delete expressions.
  epExpression__delete(expr_original);
  epExpression__delete(expr_copy);

  return 0;
}