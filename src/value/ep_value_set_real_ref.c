#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

void
epValue__set_real_ref (
  epValue *value,
  double *rRef
) {

  value->type = RREF;
  value->value.rRef = rRef;
}