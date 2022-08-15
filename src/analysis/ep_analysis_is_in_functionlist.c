#include <stdbool.h>
#include <string.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_in_functionlist (
  const char *function
) {

  unsigned int size = sizeof(epFunctionList) / sizeof(epFunctionListElement);

  for (int i = 0; i < size; i++) {
    if (strcmp(epFunctionList[i].name, function) == 0) {
      return true;
    }
  }

  return false;
}