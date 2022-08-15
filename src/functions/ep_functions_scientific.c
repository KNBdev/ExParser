#include "ep_functions.h"

//-----------------------------------------------------------------------------

double
ep_functions_scientific (
  double a,
  double b
) {

  return a * ep_functions_cpow(10, b);
}