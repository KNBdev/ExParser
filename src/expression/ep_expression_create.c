#include <stddef.h>
#include <stdlib.h>

#include "exparser.h"

#include "ep_expression.h"
#include "ep_expression_def.h"

//-----------------------------------------------------------------------------

epExpression*
epExpression__create (
  void
) {

  epExpression *expression = (epExpression *) malloc(sizeof(epExpression));
  expression->node = NULL;

  return expression;
}