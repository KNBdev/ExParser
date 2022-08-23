#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_string_balanced (
  const char *string,
  int *error
) {

  if (*error != 0) {
    return false;
  }

  unsigned int size = strlen(string);
  unsigned int buffersize = 0;
  char *braces = NULL;
  char c;

  for (int i = 0; i < size; i++) {

    *error = (i < 2) ? 1 : i;

    c = string[i];

    if (ep_analysis__is_opening_brace(c)) {

      buffersize++;
      braces = realloc(braces, sizeof(char) * buffersize);
      braces[buffersize - 1] = c;

    } else if (ep_analysis__is_closing_brace(c)) {

      if (buffersize == 0) {
        free(braces);
        return false;
      }

      if (!ep_analysis__is_brace_pair(braces[buffersize - 1], c)) {
        free(braces);
        return false;

      } else {
        buffersize--;
        braces = realloc(braces, sizeof(char) * buffersize);
      }
    }
  }

  *error = (*error == size - 1) ? 0 : *error;
  free(braces);

  return (buffersize == 0);
}