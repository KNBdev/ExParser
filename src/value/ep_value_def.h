#ifndef EP_VALUE_DEF_H
#define EP_VALUE_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>

#include "ep_value.h"

//-----------------------------------------------------------------------------

typedef enum eValue {

  R,
  RREF,
  C,
  CREF

} eValue;

//-----------------------------------------------------------------------------

typedef union uValue {

  double r;
  double *rRef;
  double complex c;
  double complex *cRef;

} uValue;

//-----------------------------------------------------------------------------

struct epValue {

  eValue type;
  uValue value;

};

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_VALUE_DEF_H