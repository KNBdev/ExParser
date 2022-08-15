#include <complex.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

double complex*
epValue__get_complex_ref (
  epValue *value
) {

  return value->value.cRef;
}