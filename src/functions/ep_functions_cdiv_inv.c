#include <complex.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

double complex
ep_functions_cdiv_inv (
  double complex a,
  double complex b
) {

  return ep_functions_cdiv(a, -b);
}