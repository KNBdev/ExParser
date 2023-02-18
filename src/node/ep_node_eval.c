#include <stdbool.h>
#include <stddef.h>

#include "ep_node.h"
#include "ep_node_def.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

epValue*
epNode__eval (
  const epNode *node
) {

  if (!node) {
    return NULL;
  }

  epValue *value = node->value;

  if (epNode__contains_function(node)) {

    bool hasLeft = (node->left);
    bool hasRight = (node->right);
    bool hasBoth = (hasLeft && hasRight);

    if (node->function.argc == ONE && hasLeft) {

      if (node->function.type == RR) {

        epValue__set_real(
          value,
          node->function.function.rr._1(
            epValue__get_real(epNode__eval(node->left))
          )
        );

      } else if (node->function.type == CR) {

        epValue__set_real(
          value,
          node->function.function.cr._1(
            epValue__get_complex(epNode__eval(node->left))
          )
        );

      } else if (node->function.type == CC) {

        epValue__set_complex(
          value,
          node->function.function.cc._1(
            epValue__get_complex(epNode__eval(node->left))
          )
        );
      }

    } else if (node->function.argc == TWO && hasBoth) {

      if (node->function.type == RR) {

        epValue__set_real(
          value,
          node->function.function.rr._2(
            epValue__get_real(epNode__eval(node->left)),
            epValue__get_real(epNode__eval(node->right))
          )
        );

      } else if (node->function.type == CR) {

        epValue__set_real(
          value,
          node->function.function.cr._2(
            epValue__get_complex(epNode__eval(node->left)),
            epValue__get_complex(epNode__eval(node->right))
          )
        );

      } else if (node->function.type == CC) {

        epValue__set_complex(
          value,
          node->function.function.cc._2(
            epValue__get_complex(epNode__eval(node->left)),
            epValue__get_complex(epNode__eval(node->right))
          )
        );
      }
    }
  }

  return value;
}