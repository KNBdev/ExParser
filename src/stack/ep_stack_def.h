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
  epValue *value;
  epFunctionListElement const *function;

} uElement;

//-----------------------------------------------------------------------------

struct epStackElement {

  epStackElement *prev;

  eElement type;
  uElement content;

};

//-----------------------------------------------------------------------------

void
epStack__init_value (
  epStack *stack
);

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