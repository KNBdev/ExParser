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

  epFunctionListElement const *f = element;
  epFunction *F = NULL;

  node->type = FUNCTION;

  F = &node->function;
  F->type = f->type;
  F->argc = f->argc;

  if (F->type == RR) {

    if (F->argc == ONE) {
      F->function.rr._1 = f->pFunction;
    } else if (F->argc == TWO) {
      F->function.rr._2 = f->pFunction;
    }

  } else if (F->type == CR) {

    if (F->argc == ONE) {
      F->function.cr._1 = f->pFunction;
    } else if (F->argc == TWO) {
      F->function.cr._2 = f->pFunction;
    }

  } else if (F->type == CC) {

    if (F->argc == ONE) {
      F->function.cc._1 = f->pFunction;
    } else if (F->argc == TWO) {
      F->function.cc._2 = f->pFunction;
    }
  }
}