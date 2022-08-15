#include <complex.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__assign_complex (
  epNode *node,
  double complex c
) {

  node->type = VALUE;
  epValue__set_complex(node->value, c);

  epNode__delete(node->left);
  epNode__delete(node->right);

  epNode__reset_children(node);
}