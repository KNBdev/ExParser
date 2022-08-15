#include "ep_functions.h"

//-----------------------------------------------------------------------------

double
ep_functions_scientific_inv (
  double a,
  double b
) {

  return a * ep_functions_cpow(10, -b);
}