#include <stddef.h>

#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__reset_children (
  epNode *node
) {

  node->left = NULL;
  node->right = NULL;
}