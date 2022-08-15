#include <stdlib.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

epValue*
epValue__create (
  void
) {

  epValue *value = malloc(sizeof(epValue));
  epValue__set_real(value, 0);

  return value;
}