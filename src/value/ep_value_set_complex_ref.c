#include <complex.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

void
epValue__set_complex_ref (
  epValue *value,
  double complex *cRef
) {

  value->type = CREF;
  value->value.cRef = cRef;
}