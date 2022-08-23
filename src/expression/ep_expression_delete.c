#include <stdlib.h>

#include "exparser.h"

#include "ep_expression_def.h"
#include "ep_node.h"

//-----------------------------------------------------------------------------

void
epExpression__delete (
  epExpression *expr
) {

  if (!expr) {
    return;
  }

  epNode__delete(expr->node);
  free(expr);

}