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
  unsigned int len;
  unsigned int i, j;

  for (i = 0; i < size; i++) {

    len = strlen(epFunctionList[i].name);

    for (j = 0; j < len; j++) {

      if (epFunctionList[i].name[j] == c) {
        return true;
      }
    }
  }

  return false;
}