#include <stddef.h>

#include "ep_functions.h"
#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__assign_function (
  epNode *node,
  epFunctionListElement const *element
) {

  epFunction *F = NULL;

  node->type = FUNCTION;

  F = &node->function;
  F->type = element->type;
  F->argc = element->argc;

  if (F->type == RR) {

    if (F->argc == ONE) {
      F->function.rr._1 = element->pFunction;
    } else if (F->argc == TWO) {
      F->function.rr._2 = element->pFunction;
    }

  } else if (F->type == CR) {

    if (F->argc == ONE) {
      F->function.cr._1 = element->pFunction;
    } else if (F->argc == TWO) {
      F->function.cr._2 = element->pFunction;
    }

  } else if (F->type == CC) {

    if (F->argc == ONE) {
      F->function.cc._1 = element->pFunction;
    } else if (F->argc == TWO) {
      F->function.cc._2 = element->pFunction;
    }
  }
}