#ifndef EP_STACK_DEF_H
#define EP_STACK_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include "ep_functions.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

typedef struct epStackElement epStackElement;

//-----------------------------------------------------------------------------

struct epStack {

  epStackElement *head;

};

//-----------------------------------------------------------------------------

typedef enum eElement {

  VALUE,
  FUNCTION,
  BRACEOPEN,
  BRACECLOSED

} eElement;

//-----------------------------------------------------------------------------

typedef union uElement {

  char brace;
  epFunctionListElement const *function;

} uElement;

//-----------------------------------------------------------------------------

struct epStackElement {

  epStackElement *prev;

  eElement type;
  uElement content;

  epValue *value;

};

//-----------------------------------------------------------------------------

void
epStack__pop (
  epStack *stack
);

void
epStack__push (
  epStack *stack
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_STACK_DEF_H