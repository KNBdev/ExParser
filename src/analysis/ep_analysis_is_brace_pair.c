#include <stdbool.h>

#include "ep_analysis.h"

//-----------------------------------------------------------------------------

bool
ep_analysis__is_brace_pair (
  char a, char b
) {

  return (a == ep_analysis__get_complementary_brace(b));
}