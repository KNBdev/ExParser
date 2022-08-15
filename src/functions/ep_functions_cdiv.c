#include <complex.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

double complex
ep_functions_cdiv (
  double complex a,
  double complex b
) {

  if (b == 0) {

    if (a == 0) {
      return NAN;

    } else {
      return INFINITY;
    }

  } else {
    return a / b;
  }
}