#include <complex.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "exparser.h"

#include "ep_analysis.h"
#include "ep_expression.h"
#include "ep_functions.h"
#include "ep_node.h"
#include "ep_stack.h"
#include "ep_value.h"
#include "ep_variables.h"

//-----------------------------------------------------------------------------

typedef struct epString {

  const char *chars;
  const unsigned int len;
  unsigned int *pos;

} epString;

//-----------------------------------------------------------------------------

static void nextChar (epString *s);
static void prevChar (epString *s);

//-----------------------------------------------------------------------------

epExpression*
epExpression__compile (
  const char *expression,
  unsigned int *error,
  epVariables *vars
) {

  //---------------------------------------------------------------------------
  // Check parameters.

  if (!expression) {
    return NULL;
  }

  unsigned int _error;

  if (!error) {
    error = &_error;
  }

  //---------------------------------------------------------------------------
  // Set up string struct,

  epString ex = {
    expression,
    strlen(expression),
    error
  };

  *(ex.pos) = 0;

  //---------------------------------------------------------------------------
  // Check for balanced expression.

  if (!ep_analysis__is_string_balanced(ex.chars, ex.pos)) {
    return NULL;
  }

  //---------------------------------------------------------------------------
  // Analyze the expression and convert it to a stack (Part I: Translation).

  epStack *stack = epStack__create();

  while (*ex.pos < ex.len) {

    //-------------------------------------------------------------------------
    // Numeric (real and imag).
    if (ep_analysis__is_numeric(ex.chars[*ex.pos])) {

      unsigned int size = 2;
      char *numeric = (char *) malloc(sizeof(char) * size);
      numeric[0] = ex.chars[*ex.pos];

      while (true) {

        nextChar(&ex);
        char c = ex.chars[*ex.pos];

        if (!ep_analysis__is_numeric(c)) {
          prevChar(&ex);
          break;
        }

        size++;

        numeric = realloc(numeric, sizeof(char) * size);
        numeric[size - 2] = c;
      }

      numeric[size - 1] = 0;
      double d = strtod(numeric, NULL);
      free(numeric);

      nextChar(&ex);

      if (ep_analysis__is_imag_unit(ex.chars[*ex.pos])) {

        epStack__push_complex(stack, d * I);

      } else {

        epStack__push_real(stack, d);
        prevChar(&ex);
      }

    //-------------------------------------------------------------------------
    // Imaginary unit.
    } else if (
      ep_analysis__is_imag_unit(ex.chars[*ex.pos])
      &&
      !isalpha(ex.chars[(*ex.pos) + 1])
    ) {

      epStack__push_complex(stack, I);

    //-------------------------------------------------------------------------
    // Function or variable.
    } else if (
      isalpha(ex.chars[*ex.pos])
      ||
      ep_analysis__is_function_char(ex.chars[*ex.pos])
    ) {

      unsigned int size = 2;
      char *literal = (char *) malloc(sizeof(char) * size);
      literal[0] = ex.chars[*ex.pos];

      while (true) {

        nextChar(&ex);
        char c = ex.chars[*ex.pos];

        if (!(isalpha(c) || ep_analysis__is_function_char(c))) {
          prevChar(&ex);
          break;
        }

        size++;

        literal = realloc(literal, sizeof(char) * size);
        literal[size - 2] = c;
      }

      literal[size - 1] = 0;

      bool isVar = false;
      char *buf = NULL;

      while (size > 0) {

        buf = realloc(buf, sizeof(char) * size);
        strncpy(buf, literal, size);
        buf[size - 1] = 0;

        if (epVariables__exists(vars, buf)) {

          if (epVariables__is_real(vars, buf)) {

            epStack__push_real_ref(
              stack,
              epVariables__get_real(vars, buf)
            );

          } else if (epVariables__is_complex(vars, buf)) {

            epStack__push_complex_ref(
              stack,
              epVariables__get_complex(vars, buf)
            );
          }

          isVar = true;
        }

        if (isVar) {
          break;

        } else if (ep_functions__exists(buf)) {

          epStack__push_function_by_name(stack, buf);

          if (ep_functions__is_unary_invert(buf)) {

            epFunctionListElement const *inv = epStack__pop_head_function(
              stack
            );

            if (epStack__is_empty(stack)) {

              epStack__push_real(stack, 0);

            } else {

              if (epStack__is_head_brace_open(stack)) {
                epStack__push_real(stack, 0);
              }
            }

            epStack__push_function_by_ref(stack, inv);
          }

          break;

        } else {
          size--;
          prevChar(&ex);
        }
      }

      free(buf);
      free(literal);

      if (size == 0) {
        break;
      }

    //-------------------------------------------------------------------------
    // Opening brace.
    } else if (ep_analysis__is_opening_brace(ex.chars[*ex.pos])) {

      epStack__push_brace_open(stack, ex.chars[*ex.pos]);

    //-------------------------------------------------------------------------
    // Closing brace.
    } else if (ep_analysis__is_closing_brace(ex.chars[*ex.pos])) {

      epStack__push_brace_closed(stack, ex.chars[*ex.pos]);
    }

    nextChar(&ex);
  }

  //---------------------------------------------------------------------------
  // Adjust error code if necessary.

  *error = (*error == ex.len) ? 0 : *error;

  if (*error != 0) {

    epStack__delete(stack);
    return NULL;
  }

  //---------------------------------------------------------------------------
  // Apply shunting yard algorithm (Part II: Analysis).

  epStack__reverse(stack);

  epStack *temp = epStack__create();
  epStack *output = epStack__create();

  while (!epStack__is_empty(stack)) {

    if (epStack__is_head_value(stack)) {

      epStack__push_value(output, epStack__pop_head_value(stack));

    } else if (epStack__is_head_function(stack)) {

      if (epStack__is_empty(temp)) {

        epStack__push_function_by_ref(temp, epStack__pop_head_function(stack));

      } else {

        epFunctionListElement const *fs = epStack__pop_head_function(stack);
        epFunctionListElement const *ft;

        while (!epStack__is_empty(temp)) {

          if (!epStack__is_head_function(temp)) {
            break;
          }

          ft = epStack__pop_head_function(temp);

          if (fs->prec <= ft->prec) {

            if (
              fs->prec == ft->prec
              &&
              ep_functions__has_right_to_left_precedence(fs)
            ) {

              epStack__push_function_by_ref(temp, fs);
              break;

            } else {

              epStack__push_function_by_ref(output, ft);
            }

          } else {
            epStack__push_function_by_ref(temp, ft);
            break;
          }
        }

        epStack__push_function_by_ref(temp, fs);
      }

    } else if (epStack__is_head_brace_open(stack)) {

      epStack__push_brace_open(temp, epStack__pop_head_brace(stack));

    } else if (epStack__is_head_brace_closed(stack)) {

      char brace = epStack__pop_head_brace(stack);

      while (true) {

        if (epStack__is_head_function(temp)) {

          epStack__push_function_by_ref(
            output,
            epStack__pop_head_function(temp)
          );

        } else {

          if (epStack__is_head_brace_open(temp)) {

            if (
              ep_analysis__is_brace_pair(
                epStack__pop_head_brace(temp),
                brace
              )
            ) {

              break;
            }
          }

          epStack__delete(temp);
          epStack__delete(output);

          return NULL;
        }
      }
    }
  }

  while (!epStack__is_empty(temp)) {

    if (epStack__is_head_function(temp)) {
      epStack__push_function_by_ref(output, epStack__pop_head_function(temp));

    } else {

      epStack__delete(temp);
      epStack__delete(output);

      return NULL;
    }
  }

  epStack__delete(stack);
  epStack__delete(temp);

  //---------------------------------------------------------------------------
  // Assemble reverse polish notation (Part III: Synthesis).

  epStack__reverse(output);

  epNode **nodeList = NULL;
  epNode *current = NULL;
  epValue *value = NULL;

  unsigned int nodeCount = 0;

  while (!epStack__is_empty(output)) {

    if (epStack__is_head_value(output)) {

      nodeCount++;
      nodeList = (epNode **) realloc(nodeList, sizeof(epNode*) * nodeCount);

      nodeList[nodeCount - 1] = epNode__create();

      value = epStack__pop_head_value(output);
      epNode__copy_value(nodeList[nodeCount - 1], value);
      epValue__delete(value);

    } else if (epStack__is_head_function(output)) {

      epFunctionListElement const *function = epStack__pop_head_function(
        output
      );

      current = epNode__create();
      epNode__assign_function(current, function);

      if (function->argc == ONE && nodeCount >= 1) {

        epNode__assign_left(current, nodeList[nodeCount - 1]);

      } else if (function->argc == TWO && nodeCount >= 2) {

        epNode__assign_left(current, nodeList[nodeCount - 2]);
        epNode__assign_right(current, nodeList[nodeCount - 1]);

        nodeCount--;
        nodeList = (epNode **) realloc(nodeList, sizeof(epNode*) * nodeCount);
      }

      nodeList[nodeCount - 1] = current;
    }
  }

  epStack__delete(output);

  if (nodeCount != 1) {

    *error = ex.len;
    free(nodeList);

    return NULL;
  }

  //---------------------------------------------------------------------------
  // Assign node tree to expression.

  epExpression *expr = epExpression__create();
  epExpression__assign_node(expr, nodeList[0]);

  epNode__reduce(nodeList[0]);
  free(nodeList);

  return expr;
}

//-----------------------------------------------------------------------------

static void
nextChar (
  epString *s
) {

  while (*s->pos < s->len) {
    (*s->pos)++;
    if (!isspace(s->chars[*s->pos])) {
      break;
    }
  }
}

//-----------------------------------------------------------------------------

static void
prevChar (
  epString *s
) {

  while (*s->pos > 0) {
    (*s->pos)--;
    if (!isspace(s->chars[*s->pos])) {
      break;
    }
  }
}
