#include <stddef.h>

#include "exparser.h"

#include "ep_expression.h"
#include "ep_expression_def.h"

//-----------------------------------------------------------------------------

epExpression*
epExpression__duplicate (
  const epExpression *expr
) {

  if (!expr) {
    return NULL;
  }

  epExpression *new = epExpression__create();
  epExpression__assign_node(new, epNode__copy_node_recursively(expr->node));

  return new;
}