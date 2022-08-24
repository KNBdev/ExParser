#include <complex.h>

#include "exparser.h"

#include "ep_node.h"
#include "ep_expression_def.h"

//-----------------------------------------------------------------------------

void
epExpression__replace_complex_variable (
  epExpression *expr,
  double complex *c_old,
  double complex *c_new
) {

  epNode__replace_recursively_complex_ref(expr->node, c_old, c_new);
}