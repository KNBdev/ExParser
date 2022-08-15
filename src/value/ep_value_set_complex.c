#include <complex.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

void
epValue__set_complex (
  epValue *value,
  double complex c
) {

  if (cimag(c) == 0) {

    epValue__set_real(value, creal(c));

  } else {

    value->type = C;
    value->value.c = c;
  }
}