#ifndef EP_NODE_H
#define EP_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

#include "ep_functions.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

typedef struct epNode epNode;

//-----------------------------------------------------------------------------

epNode*
epNode__create (
  void
);

void
epNode__delete (
  epNode *node
);

void
epNode__assign_left (
  epNode *node,
  epNode *left
);

void
epNode__assign_right (
  epNode *node,
  epNode *right
);

epValue*
epNode__eval (
  epNode *node
);

void
epNode__assign_function (
  epNode *node,
  epFunctionListElement const *element
);

void
epNode__assign_real (
  epNode *node,
  double r
);

void
epNode__assign_real_ref (
  epNode *node,
  double *rRef
);

void
epNode__assign_complex (
  epNode *node,
  double complex c
);

void
epNode__assign_complex_ref (
  epNode *node,
  double complex *cRef
);

void
epNode__copy_value (
  epNode *node,
  epValue *value
);

epNode*
epNode__copy_node_recursively (
  epNode *node
);

void
epNode__replace_recursively_real_ref (
  epNode *node,
  double *r_old,
  double *r_new
);

void
epNode__replace_recursively_complex_ref (
  epNode *node,
  double complex *c_old,
  double complex *c_new
);

bool
epNode__reduce (
  epNode* node
);

void
epNode__reset_children (
  epNode* node
);

bool
epNode__contains_function (
  epNode *node
);

bool
epNode__contains_value (
  epNode *node
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_NODE_H