#include <stdbool.h>
#include <string.h>

#include "ep_analysis.h"
#include "ep_functions.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_function_char (
  char c
) {

  unsigned int size = sizeof(epFunctionList) / sizeof(epFunctionListElement);

  for (unsigned int i = 0; i < size; i++) {

    unsigned int len = strlen(epFunctionList[i].name);

    for (unsigned int j = 0; j < len; j++) {

      if (epFunctionList[i].name[j] == c) {
        return true;
      }
    }
  }

  return false;
}