#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__copy_value (
  epNode *node,
  epValue *value
) {

  if (!value) {
    return;
  }

  node->type = VALUE;
  epValue__copy(node->value, value);

  epNode__delete(node->left);
  epNode__delete(node->right);

  epNode__reset_children(node);
}