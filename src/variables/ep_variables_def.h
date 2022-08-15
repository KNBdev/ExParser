#ifndef EP_VARIABLES_DEF_H
#define EP_VARIABLES_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>

#include "exparser.h"
#include "ep_variables.h"

//-----------------------------------------------------------------------------

typedef struct epVariable {

  const char *name;

  enum {
    R,
    C
  } type;

  union {
    double *r;
    double complex *c;
  } p;

} epVariable;

//-----------------------------------------------------------------------------

struct epVariables {

  epVariable *vars;
  unsigned int amount;
};

//-----------------------------------------------------------------------------

void
epVariables__add (
  epVariables *vars,
  epVariable var
);

int
epVariables__exists_at (
  epVariables *vars,
  const char *name
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_VARIABLES_DEF_H