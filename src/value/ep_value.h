#ifndef EP_VALUE_H
#define EP_VALUE_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

typedef struct epValue epValue;

//-----------------------------------------------------------------------------

epValue*
epValue__create (
  void
);

void
epValue__delete (
  epValue *value
);

//---------------

bool
epValue__is_real (
  const epValue *value
);

bool
epValue__is_real_ref (
  const epValue *value
);

bool
epValue__is_complex (
  const epValue *value
);

bool
epValue__is_complex_ref (
  const epValue *value
);

//-----------------------

double
epValue__get_real (
  const epValue *value
);

double*
epValue__get_real_ref (
  const epValue *value
);

double complex
epValue__get_complex (
  const epValue *value
);

double complex*
epValue__get_complex_ref (
  const epValue *value
);

//--------------------

void
epValue__set_real (
  epValue *value,
  double r
);

void
epValue__set_real_ref (
  epValue *value,
  double *rRef
);

void
epValue__set_complex (
  epValue *value,
  double complex c
);

void
epValue__set_complex_ref (
  epValue *value,
  double complex *cRef
);

//------------------------

void
epValue__copy (
  epValue *dest,
  const epValue *src
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_VALUE_H