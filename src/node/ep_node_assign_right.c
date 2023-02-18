#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__assign_right (
  epNode *node,
  epNode* const right
) {

  node->right = right;
}