#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__assign_real_ref (
  epNode *node,
  double *rRef
) {

  node->type = VALUE;
  epValue__set_real_ref(node->value, rRef);

  epNode__delete(node->left);
  epNode__delete(node->right);

  epNode__reset_children(node);
}