#include <stdbool.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_opening_brace (
  char c
) {

  return (c == '(' || c == '[' || c == '{');
}