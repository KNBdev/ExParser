#include <complex.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__assign_complex_ref (
  epNode *node,
  double complex *cRef
) {

  node->type = VALUE;
  epValue__set_complex_ref(node->value, cRef);

  epNode__delete(node->left);
  epNode__delete(node->right);

  epNode__reset_children(node);
}