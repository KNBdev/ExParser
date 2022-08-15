#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__assign_real (
  epNode *node,
  double r
) {

  node->type = VALUE;
  epValue__set_real(node->value, r);

  epNode__delete(node->left);
  epNode__delete(node->right);

  epNode__reset_children(node);
}