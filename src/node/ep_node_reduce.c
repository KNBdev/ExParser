#include <stdbool.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

bool
epNode__reduce (
  epNode* node
) {

  // Check for empty node slot.
  if (!node) {
    return true;
  }

  // Get value.
  epValue* value = node->value;

  // Node contains value.
  if (epNode__contains_value(node)) {

    return (!epValue__is_real_ref(value) && !epValue__is_complex_ref(value));

  // Node contains function.
  } else if (epNode__contains_function(node)) {

    // Reduce sub-nodes.
    bool reduceLeft = epNode__reduce(node->left);
    bool reduceRight = epNode__reduce(node->right);

    // Combine bools from sub-nodes.
    bool isReducable = reduceLeft && reduceRight;

    // Both sub-nodes are constant.
    if (isReducable) {

      // Set value directly.
      epValue__copy(value, epNode__eval(node));
      node->type = VALUE;

      // Remove sub nodes.
      epNode__delete(node->left);
      epNode__delete(node->right);
      epNode__reset_children(node);
    }

    return isReducable;
  }

  return false;
}