#ifndef EP_EXPRESSION_H
#define EP_EXPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include "exparser.h"

#include "ep_node.h"

//-----------------------------------------------------------------------------

epExpression*
epExpression__create (
  void
);

void
epExpression__assign_node (
  epExpression *expression,
  epNode* const node
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_EXPRESSION_H