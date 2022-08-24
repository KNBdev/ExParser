#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__replace_recursively_real_ref (
  epNode *node,
  double *r_old,
  double *r_new
) {

  if (!node) {
    return;
  }

  if (epNode__contains_value(node)) {
    if (epValue__is_real_ref(node->value)) {
      if (epValue__get_real_ref(node->value) == r_old) {
        epValue__set_real_ref(node->value, r_new);
      }
    }
  }

  epNode__replace_recursively_real_ref(node->left, r_old, r_new);
  epNode__replace_recursively_real_ref(node->right, r_old, r_new);
}