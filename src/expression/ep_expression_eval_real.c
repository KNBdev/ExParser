#include "exparser.h"

#include "ep_expression_def.h"
#include "ep_node.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

double
epExpression__eval_real (
  epExpression *expression
) {

  return epValue__get_real(epNode__eval(expression->node));
}