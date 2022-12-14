#include <string.h>

#include "ep_functions.h"

//-----------------------------------------------------------------------------

int
ep_functions__exists_at (
  const char *function
) {

  unsigned int size = sizeof(epFunctionList) / sizeof(epFunctionListElement);

  for (int i = 0; i < size; i++) {
    if (strcmp(epFunctionList[i].name, function) == 0) {
      return i;
    }
  }

  return -1;
}