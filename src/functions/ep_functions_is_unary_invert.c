#include <stdbool.h>
#include <string.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

bool
ep_functions__is_unary_invert (
  const char *name
) {

  return (strcmp(name, "-") == 0);
}