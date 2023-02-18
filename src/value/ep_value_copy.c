#include "ep_value.h"
#include "ep_value_def.h"

//-----------------------------------------------------------------------------

void
epValue__copy (
  epValue *dest,
  const epValue *src
) {

  *dest = *src;
}