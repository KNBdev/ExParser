#include <stdbool.h>

#include "ep_node.h"
#include "ep_node_def.h"

//-----------------------------------------------------------------------------

bool
epNode__contains_function (
  epNode *node
) {

  return (node->type == FUNCTION);
}