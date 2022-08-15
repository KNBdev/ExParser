#include <complex.h>
#include <stdlib.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

double complex
ep_functions_cpow (
  double complex a,
  double complex b
) {

  if (cimag(b) != 0) {
    return cpow(a, b);
  }

  double _b = creal(b);

  if (ep_functions_mod(_b, 1) != 0) {
    return cpow(a, b);
  }

  if (_b == 0) {

    if (a == 0) {
      return NAN;

    } else {
      return 1;
    }

  } else if (_b == 1) {
    return a;
  }

  int exponent_abs = abs((int) _b);
  double complex _a = a;

  for (unsigned int i = 1; i < exponent_abs; i++) {
    a *= _a;
  }

  if (_b > 0) {
    return a;

  } else {
    return 1 / a;
  }
}