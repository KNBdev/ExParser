#include <stdbool.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

bool
ep_functions__has_right_to_left_precedence (
  const epFunctionListElement * const function
) {

  switch (function->prec) {

    case POWER:
    case F:
      return true;

    default:
      return false;
  }
}
