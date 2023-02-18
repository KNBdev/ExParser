#include <stdbool.h>

#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

bool
epValue__is_complex (
  const epValue *value
) {

  return (value->type == C);
}