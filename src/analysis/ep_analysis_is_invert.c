#include <stdbool.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_invert (
  char c
) {

  return (c == ep_analysis__get_invert());
}