#include <stdbool.h>
#include <string.h>

#include "exparser.h"

#include "ep_analysis.h"
#include "ep_variables.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_variable_char (
  epVariables *vars,
  char c
) {

  if (!vars) {
    return false;
  }

  unsigned int amount = epVariables__get_amount(vars);

  for (unsigned int i = 0; i < amount; i++) {

    char const *name = epVariables__get_name_by_index(vars, i);
    unsigned int len = strlen(name);

    for (unsigned int j = 0; j < len; j++) {

      if (name[j] == c) {
        return true;
      }
    }
  }

  return false;
}