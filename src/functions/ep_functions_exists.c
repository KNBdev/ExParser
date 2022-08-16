#include <stdbool.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

bool
ep_functions__exists (
  const char *name
) {

  return (ep_functions__exists_at(name) != -1);
}