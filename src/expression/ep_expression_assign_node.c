#include "ep_expression.h"
#include "ep_expression_def.h"
#include "ep_node.h"

//-----------------------------------------------------------------------------

void
epExpression__assign_node (
  epExpression *expression,
  epNode *node
) {

  expression->node = node;
}