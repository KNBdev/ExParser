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
  unsigned int *error,
  epVariables *vars
);

double
epExpression__eval_real (
  epExpression *expr
);

double complex
epExpression__eval_complex (
  epExpression *expr
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