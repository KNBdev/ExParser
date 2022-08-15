#include <stdlib.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

void
epValue__delete (
  epValue *value
) {

  free(value);
}