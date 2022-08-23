#include <stdbool.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

bool
epNode__reduce (
  epNode* node
) {

  if (!node) {
    return true;

  } else if (epNode__contains_value(node)) {

    epValue *value = node->value;
    return (epValue__is_real(value) || epValue__is_complex(value));

  } else if (epNode__contains_function(node)) {

    bool isLeftConstant = epNode__reduce(node->left);
    bool isRightConstant = epNode__reduce(node->right);

    if (isLeftConstant && isRightConstant) {

      epNode__eval(node);

      epNode__delete(node->left);
      epNode__delete(node->right);

      epNode__reset_children(node);

      return true;

    } else {

      return false;
    }
  }
}