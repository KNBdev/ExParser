#include <complex.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

double complex
ep_functions_cmul_inv (
  double complex a,
  double complex b
) {

  return ep_functions_cmul(a, -b);
}