#include <complex.h>

#include "exparser.h"

#include "ep_expression_def.h"
#include "ep_node.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

double complex
epExpression__eval_complex (
  const epExpression *expression
) {

  return epValue__get_complex(epNode__eval(expression->node));
}