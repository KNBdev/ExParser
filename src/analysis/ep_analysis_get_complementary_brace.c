#include "ep_analysis.h"

//-----------------------------------------------------------------------------

char
ep_analysis__get_complementary_brace (
  char a
) {

  switch (a) {

    case '(':
      return ')';

    case ')':
      return '(';

    case '[':
      return ']';

    case ']':
      return '[';

    case '{':
      return '}';

    case '}':
      return '{';
  }

  return 0;
}