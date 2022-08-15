#include <stdlib.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__delete (
  epNode *node
) {

  if (!node) {
    return;
  }

  epNode__delete(node->left);
  epNode__delete(node->right);

  epValue__delete(node->value);

  free(node);
}