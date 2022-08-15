#ifndef EP_NODE_DEF_H
#define EP_NODE_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include "ep_functions.h"
#include "ep_node.h"
#include "ep_value.h"

//-----------------------------------------------------------------------------

typedef enum eContent {

  VALUE,
  FUNCTION

} eContent;

//-----------------------------------------------------------------------------

struct epNode {

  epNode *left;
  epNode *right;

  eContent type;

  epValue *value;
  epFunction function;
};

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_NODE_DEF_H