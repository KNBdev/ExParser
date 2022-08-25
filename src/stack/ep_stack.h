#ifndef EP_STACK_H
#define EP_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <stdbool.h>

#include "ep_functions.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

typedef struct epStack epStack;

//-----------------------------------------------------------------------------

epStack*
epStack__create (
  void
);

void
epStack__delete (
  epStack *stack
);

void
epStack__push_real (
  epStack *stack,
  double r
);

void
epStack__push_real_ref (
  epStack *stack,
  double *rRef
);

void
epStack__push_complex (
  epStack *stack,
  double complex c
);

void
epStack__push_complex_ref (
  epStack *stack,
  double complex *cRef
);

void
epStack__push_value (
  epStack *stack,
  epValue *value
);

void
epStack__push_function_by_name (
  epStack *stack,
  const char *name
);

void
epStack__push_function_by_ref (
  epStack *stack,
  epFunctionListElement const *function
);

void
epStack__push_brace_open (
  epStack *stack,
  char brace
);

void
epStack__push_brace_closed (
  epStack *stack,
  char brace
);

void
epStack__reverse (
  epStack *stack
);

void
epStack__init_head_value (
  epStack *stack
);

//-----------------------------------------------------------------------------

bool
epStack__is_head_value (
  epStack *stack
);

bool
epStack__is_head_function (
  epStack *stack
);

bool
epStack__is_head_brace_open (
  epStack *stack
);

bool
epStack__is_head_brace_closed (
  epStack *stack
);

bool
epStack__is_empty (
  epStack *stack
);

//-----------------------------------------------------------------------------

epValue*
epStack__pop_head_value (
  epStack *stack
);

epFunctionListElement const*
epStack__pop_head_function (
  epStack *stack
);

char
epStack__pop_head_brace (
  epStack *stack
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_STACK_H