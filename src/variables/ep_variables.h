#ifndef EP_VARIABLES_H
#define EP_VARIABLES_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <stdbool.h>

#include "exparser.h"

//-----------------------------------------------------------------------------

bool
epVariables__exists (
  epVariables *vars,
  const char *name
);

bool
epVariables__is_real (
  epVariables *vars,
  const char *name
);

bool
epVariables__is_complex (
  epVariables *vars,
  const char *name
);

double*
epVariables__get_real (
  epVariables *vars,
  const char *name
);

double complex*
epVariables__get_complex (
  epVariables *vars,
  const char *name
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_VARIABLES_H