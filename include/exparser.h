#ifndef EXPARSER_H
#define EXPARSER_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>

//-----------------------------------------------------------------------------
// Types.

typedef struct epExpression epExpression;
typedef struct epVariables epVariables;

//-----------------------------------------------------------------------------
// epVariables.

epVariables*
epVariables__create (
  void
);

void
epVariables__add_real (
  epVariables *vars,
  const char *name,
  double *r
);

void
epVariables__add_complex (
  epVariables *vars,
  const char *name,
  double complex *c
);

void
epVariables__delete (
  epVariables *vars
);

//-----------------------------------------------------------------------------
// epExpression.

epExpression*
epExpression__compile (
  const char *expr,
  int *error,
  const epVariables *vars
);

epExpression*
epExpression__duplicate (
  const epExpression *expr
);

void
epExpression__replace_real_variable (
  epExpression *expr,
  double *r_old,
  double *r_new
);

void
epExpression__replace_complex_variable (
  epExpression *expr,
  double complex *c_old,
  double complex *c_new
);

double
epExpression__eval_real (
  const epExpression *expr
);

double complex
epExpression__eval_complex (
  const epExpression *expr
);

void
epExpression__delete (
  epExpression *expr
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EXPARSER_H