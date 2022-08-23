#include <stdlib.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

epNode*
epNode__create (
  void
) {

  epNode *node = malloc(sizeof(epNode));

  node->left = NULL;
  node->right = NULL;
  node->type = VALUE;
  node->value = epValue__create();

  return node;
}