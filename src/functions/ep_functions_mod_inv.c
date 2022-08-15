#include "ep_functions.h"

//-----------------------------------------------------------------------------

double
ep_functions_mod_inv (
  double a,
  double b
) {

  return ep_functions_mod(a, -b);
}