#include "ep_value.h"
#include "ep_value_def.h"

#include <stdio.h>

//-----------------------------------------------------------------------------

void
epValue__set_real (
  epValue *value,
  double r
) {

  value->type = R;
  value->value.r = r;
}