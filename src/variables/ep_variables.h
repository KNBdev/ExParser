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
  const epVariables *vars,
  const char *name
);

bool
epVariables__is_real (
  const epVariables *vars,
  const char *name
);

bool
epVariables__is_complex (
  const epVariables *vars,
  const char *name
);

double*
epVariables__get_real (
  const epVariables *vars,
  const char *name
);

double complex*
epVariables__get_complex (
  const epVariables *vars,
  const char *name
);

unsigned int
epVariables__get_amount (
  const epVariables *vars
);

const char*
epVariables__get_name_by_index (
  const epVariables *vars,
  unsigned int index
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_VARIABLES_H