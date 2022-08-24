#include <complex.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

void
epNode__replace_recursively_complex_ref (
  epNode *node,
  double complex *c_old,
  double complex *c_new
) {

  if (!node) {
    return;
  }

  if (epNode__contains_value(node)) {
    if (epValue__is_complex_ref(node->value)) {
      if (epValue__get_complex_ref(node->value) == c_old) {
        epValue__set_complex_ref(node->value, c_new);
      }
    }
  }

  epNode__replace_recursively_complex_ref(node->left, c_old, c_new);
  epNode__replace_recursively_complex_ref(node->right, c_old, c_new);
}