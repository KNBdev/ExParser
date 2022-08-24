#include "exparser.h"

#include "ep_node.h"
#include "ep_expression_def.h"

//-----------------------------------------------------------------------------

void
epExpression__replace_real_variable (
  epExpression *expr,
  double *r_old,
  double *r_new
) {

  epNode__replace_recursively_real_ref(expr->node, r_old, r_new);
}