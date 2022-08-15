#include <stdbool.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_imag_unit (
  char c
) {

  return (c == 'i');
}