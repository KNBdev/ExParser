#include <stdbool.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_numeric (
  char c
) {

  return (('0' <= c && c <= '9') || c == '.');
}