#include <complex.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

double
epValue__get_real (
  const epValue *value
) {

  if (epValue__is_real(value)) {
    return value->value.r;

  } else if (epValue__is_real_ref(value)) {
    return *(value->value.rRef);

  } else if (epValue__is_complex(value)) {
    return creal(value->value.c);

  } else if (epValue__is_complex_ref(value)) {
    return creal(*(value->value.cRef));
  }
}