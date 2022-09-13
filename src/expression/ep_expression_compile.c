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
  int *pos;

} epString;

//-----------------------------------------------------------------------------

static void nextChar (epString *s);
static void prevChar (epString *s);
static char currChar (epString *s);
static char pcurChar (epString *s);

static epStack* string_to_stack (epString *s, epVariables *vars);
static epStack* stack_to_rpn_stack (epStack *stack, int *error);
static epNode* rpn_stack_to_node (epStack *rpn, int *error);

//-----------------------------------------------------------------------------

epExpression*
epExpression__compile (
  const char *expression,
  int *error,
  epVariables *vars
) {

  if (!expression) {
    return NULL;
  }

  int _error;

  if (!error) {
    error = &_error;
  }

  *error = 0;

  epString ex = {
    expression,
    strlen(expression),
    error
  };

  if (!ep_analysis__is_string_balanced(ex.chars, ex.pos)) {
    return NULL;
  }

  epStack *stack = string_to_stack(&ex, vars);

  if (!stack) {
    return NULL;
  }

  epStack *rpn = stack_to_rpn_stack(stack, error);

  if (!rpn) {
    return NULL;
  }

  epNode *node = rpn_stack_to_node(rpn, error);

  if (!node) {
    return NULL;
  }

  epExpression *expr = epExpression__create();
  epExpression__assign_node(expr, node);

  return expr;
}

//-----------------------------------------------------------------------------

static void
nextChar (
  epString *s
) {

  while (*s->pos < s->len) {
    (*s->pos)++;
    if (!isspace(currChar(s))) {
      break;
    }
  }
}

//-------------------------------------

static void
prevChar (
  epString *s
) {

  while (*s->pos > 0) {
    (*s->pos)--;
    if (!isspace(currChar(s))) {
      break;
    }
  }
}

//-------------------------------------

static char
currChar (
  epString *s
) {

  return s->chars[*s->pos];
}

//-------------------------------------

static char
pcurChar (
  epString *s
) {

  return s->chars[(*s->pos) + 1];
}

//-----------------------------------------------------------------------------

static epStack*
string_to_stack (
  epString *s,
  epVariables *vars
) {

  epStack *stack = epStack__create();

  while (*s->pos < s->len) {

    //-------------------------------------------------------------------------
    // Numeric (real and imag).
    if (
      ep_analysis__is_numeric(currChar(s))
      ||
      (
        ep_analysis__is_invert(currChar(s))
        &&
        ep_analysis__is_numeric(pcurChar(s))
      )
    ) {

      unsigned int string_len = 2;
      char *string = (char *) malloc(sizeof(char) * string_len);
      string[0] = currChar(s);

      while (true) {

        nextChar(s);
        char c = currChar(s);

        if (!ep_analysis__is_numeric(c)) {
          prevChar(s);
          break;
        }

        string_len++;
        string = realloc(string, sizeof(char) * string_len);
        string[string_len - 2] = c;
      }

      string[string_len - 1] = 0;
      double d = atof(string);
      free(string);

      nextChar(s);

      if (ep_analysis__is_imag_unit(currChar(s))) {

        epStack__push_complex(stack, d * I);

      } else {

        epStack__push_real(stack, d);
        prevChar(s);
      }

    //-------------------------------------------------------------------------
    // Imaginary unit.
    } else if (
      ep_analysis__is_imag_unit(currChar(s))
      &&
      !isalpha(pcurChar(s))
    ) {

      epStack__push_complex(stack, I);

    //-------------------------------------------------------------------------
    // Function or variable.
    } else if (
      ep_analysis__is_function_char(currChar(s))
      ||
      ep_analysis__is_variable_char(vars, currChar(s))
    ) {

      unsigned int string_len = 2;
      char *string = (char *) malloc(sizeof(char) * string_len);
      string[0] = currChar(s);

      while (true) {

        nextChar(s);
        char c = currChar(s);

        if (
          !(
            ep_analysis__is_function_char(c)
            ||
            ep_analysis__is_variable_char(vars, c)
          )
        ) {

          prevChar(s);
          break;
        }

        string_len++;
        string = realloc(string, sizeof(char) * string_len);
        string[string_len - 2] = c;
      }

      string[string_len - 1] = 0;
      char *buffer = NULL;
      unsigned int buffersize = string_len;

      while (buffersize > 1) {

        buffer = realloc(buffer, sizeof(char) * buffersize);
        strncpy(buffer, string, buffersize);
        buffer[buffersize - 1] = 0;

        if (ep_functions__exists(buffer)) {

          epStack__push_function_by_name(stack, buffer);

          epFunctionListElement const *cur = epStack__pop_head_function(stack);

          if (!epStack__is_empty(stack)) {
            if (epStack__is_head_function(stack)) {

              if (cur->argc == TWO) {
                buffersize = 1;
                break;
              }
            }
          }

          epStack__push_function_by_ref(stack, cur);

          if (buffersize == 2 && ep_analysis__is_invert(buffer[0])) {

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

        } else if (epVariables__exists(vars, buffer)) {

          if (epVariables__is_real(vars, buffer)) {

            epStack__push_real_ref(
              stack,
              epVariables__get_real(vars, buffer)
            );

          } else if (epVariables__is_complex(vars, buffer)) {

            epStack__push_complex_ref(
              stack,
              epVariables__get_complex(vars, buffer)
            );
          }

          break;
        }

        buffersize--;
        prevChar(s);
      }

      free(string);
      free(buffer);

      if (buffersize == 1) {
        break;
      }

    //-------------------------------------------------------------------------
    // Opening brace.
    } else if (ep_analysis__is_opening_brace(currChar(s))) {

      epStack__push_brace_open(stack, currChar(s));

    //-------------------------------------------------------------------------
    // Closing brace.
    } else if (ep_analysis__is_closing_brace(currChar(s))) {

      if (!epStack__is_empty(stack)) {
        if (epStack__is_head_function(stack)) {
          break;
        }
      }

      epStack__push_brace_closed(stack, currChar(s));

    //-------------------------------------------------------------------------
    // No fit.
    } else {
      break;
    }

    nextChar(s);
  }

  *s->pos = (*s->pos == s->len) ? 0 : *s->pos;

  if (*s->pos != 0) {

    epStack__delete(stack);
    return NULL;
  }

  epStack__reverse(stack);
  return stack;
}

//-----------------------------------------------------------------------------

static epStack*
stack_to_rpn_stack (
  epStack *stack,
  int *error
) {

  epStack *temp = epStack__create();
  epStack *rpn = epStack__create();

  while (!epStack__is_empty(stack)) {

    if (epStack__is_head_value(stack)) {

      epStack__push_value(rpn, epStack__pop_head_value(stack));

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

              epStack__push_function_by_ref(temp, ft);
              break;

            } else {

              epStack__push_function_by_ref(rpn, ft);
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
            rpn,
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

          epStack__delete(stack);
          epStack__delete(temp);
          epStack__delete(rpn);

          return NULL;
        }
      }
    }
  }

  while (!epStack__is_empty(temp)) {

    if (epStack__is_head_function(temp)) {
      epStack__push_function_by_ref(rpn, epStack__pop_head_function(temp));

    } else {

      epStack__delete(stack);
      epStack__delete(temp);
      epStack__delete(rpn);

      return NULL;
    }
  }

  epStack__delete(stack);
  epStack__delete(temp);

  epStack__reverse(rpn);

  return rpn;
}

//-----------------------------------------------------------------------------

static epNode*
rpn_stack_to_node (
  epStack *rpn,
  int *error
) {

  epNode **nodeList = NULL;
  epNode *current = NULL;
  epValue *value = NULL;

  int nodeCount = 0;

  while (!epStack__is_empty(rpn)) {

    if (epStack__is_head_value(rpn)) {

      nodeCount++;
      nodeList = (epNode **) realloc(nodeList, sizeof(epNode*) * nodeCount);

      nodeList[nodeCount - 1] = epNode__create();

      epValue *value = epStack__pop_head_value(rpn);

      epNode__copy_value(
        nodeList[nodeCount - 1],
        value
      );

    } else if (epStack__is_head_function(rpn)) {

      epFunctionListElement const *function = epStack__pop_head_function(
        rpn
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

      } else {

        *error = -1;
        break;
      }

      nodeList[nodeCount - 1] = current;
    }
  }

  epStack__delete(rpn);

  if (nodeCount != 1 || *error == -1) {

    for (unsigned int i = 0; i < nodeCount; i++) {
      epNode__delete(nodeList[i]);
    }

    *error = -1;
    free(nodeList);

    return NULL;
  }

  epNode *node = nodeList[0];
  free(nodeList);

  epNode__reduce(node);
  return node;
}
