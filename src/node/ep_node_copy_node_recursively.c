#include <stddef.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

epNode*
epNode__copy_node_recursively (
  const epNode *node
) {

  if (!node) {
    return NULL;
  }

  epNode *new = epNode__create();

  new->type = node->type;
  new->function = node->function;

  new->value = epValue__create();
  epValue__copy(new->value, node->value);

  epNode__assign_left(new, epNode__copy_node_recursively(node->left));
  epNode__assign_right(new, epNode__copy_node_recursively(node->right));

  return new;
}