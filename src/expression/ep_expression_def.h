#ifndef EP_EXPRESSION_DEF_H
#define EP_EXPRESSION_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include "exparser.h"

#include "ep_node.h"

//-----------------------------------------------------------------------------

struct epExpression {

  epNode *node;
};

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_EXPRESSION_DEF_H