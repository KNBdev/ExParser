#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

void
epNode__assign_left (
  epNode *node,
  epNode* const left
) {

  node->left = left;
}