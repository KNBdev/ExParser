# ExParser

A mathematical **ex**pression **parser** written in C, able to handle real and complex inputs alongside a variety of commonly used functions for both real and complex evaluation.

This parser was created out of the need for one, heavily inspired by [CodePlea](https://github.com/codeplea/)'s amazing math expression parser [tinyexpr](https://github.com/codeplea/tinyexpr).

The theory behind this parser relies on the application of the [shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm). Based on this algorithm a recursive node tree is constructed and stored inside an expression structure which then can be evaluated.

## Features

- Written in C99
- Dependent only on the C standard library
- Evaluation without recompilation of the expression
- Usage of both real and complex variables
- Evaluation routine is optimized for speed
- Compiling routine condenses constant parts of the expression
- Powers with whole number exponents are optimized in evaluation
- Further supports:
  + Scientific notation: `1e10`, `2e-5`, …
  + Unary invert: `-3 + …`, `(-5 + 9i)`, `4 *- 2`, `7 /- sin(8i)`, …

## Building

### With Make

Go to the root directory, open a terminal and compile the source with:

```
$ make
```

The library will then be located at `./build/lib/`.

### Without Make

Follow the steps in exactly this or a similar manner, starting at the root directory:

1. Make build directory. <br/> `$ mkdir build`
2. Enter build directory. <br/> `$ cd build/`
3. Copy all header files and source files into the build directory. <br/> `$ cp -r ../include/*.h ../src/*/*.h ../src/*/*.c .`
4. Compile all source files without linking. <br/> `$ gcc -c *.c`
5. Create a static library archive. <br/> `$ ar rcs libexparser.a *.o`

## Usage

### Include flags

To use the library, simply include the ExParser header into your project.

```c
#include "exparser.h"
```

The library provides several functions, all declared in the header file. There are functions for the expression itself and for a variable container that is used during the expression compiling.

### Variables

ExParser provides a simple method to assign real and complex variables to your expression by using a variable container. The functions regarding the variable container are shown below.

- `epVariables* epVariables__create (void);` <br/> Initialize the container.
- `void epVariables__add_real (epVariables *vars, const char *name, double *r);` <br/> Add a real variable to the container.
- `void epVariables__add_complex (epVariables *vars, const char *name, double complex *c);` <br/> Add a complex variable to the container.
- `void epVariables__delete (epVariables *vars);` <br/> Delete the variable container.

### Expressions

This library provides an expression structure to operate on. The following functions are declared in the header:

- `epExpression* epExpression__compile (const char *expr, unsigned int *error, epVariables *vars);` <br/> Compile an expression string into an expression struct.
- `double epExpression__eval_real (epExpression *expr);` <br/> Evaluate an expression struct to a real value.
- `double complex epExpression__eval_complex (epExpression *expr);` <br/> Evaluate an expression struct to a complex value.
- `void epExpression__delete (epExpression *expr);` <br/> Delete an expression struct.

### Compilation

To compile your project with ExParser, simply link the static library alongside with the math library. Don't forget to tell the compiler where to find everything.

```
$ gcc … \
  -I<path-to-directory-containing-exparser.h> \
  -L<path-to-directory-containing-libexparser.a> \
  -lexparser -lm …
```

or

```
$ gcc … -I<path-to-directory-containing-exparser.h> <path-to>/libexparser.a -lm …
```

## Complete example

The following example contains all above mentioned functions.

```c
#include <complex.h>
#include <stdio.h>

#include "exparser.h"

//-------------------------------------

int main (void) {

  // Declare expression strings.
  const char *string_r = "cosh(r^-3) - sin(5/r)";
  const char *string_c = "exp(i/c)^r / sin(3+4i)";

  // Create variables.
  double r = 5;
  double complex c = 3 - 7 * I;

  // Set up variable container.
  epVariables *vars = epVariables__create();

  // Add a real variable.
  epVariables__add_real(vars, "r", &r);

  // Add a complex variable.
  epVariables__add_complex(vars, "c", &c);

  // Set up an integer variable that holds the compilation error code.
  unsigned int error;

  // Compile the expressions, use error code and variable container.
  epExpression *expression_r = epExpression__compile(string_r, &error, vars);
  epExpression *expression_c = epExpression__compile(string_c, NULL, vars);

  // Check if expressions have been compiled successfully.
  if (!expression_r || !expression_c) {

    printf("Error occured during compilation! Abort execution!\n");
    epVariables__delete(vars);
    epExpression__delete(expression_r);
    epExpression__delete(expression_c);

    return 1;
  }

  // After compilation, there is no further use for the variable container.
  epVariables__delete(vars);

  // Evaluate complex expression.
  double result_r = epExpression__eval_real(expression_r);
  double complex result_c = epExpression__eval_complex(expression_c);

  // Delete expressions.
  epExpression__delete(expression_r);
  epExpression__delete(expression_c);

  // Print results.
  printf("Real expression evaluates to: %f\n", result_r);
  printf("Complex expression evaluates to: %f + %f * i\n", creal(result_c), cimag(result_c));

  return 0;
}
```

Compile this with the instructions given at the entry [Compilation](#Compilation). Executing this code should result in the following output:

```
Real expression evaluates to: 0.158561
Complex expression evaluates to: -0.002338 + 0.019904 * i
```

## Advices

The parser handles a lot for you, but there are a few things that the parser is not concepted for. Here are some things to remember while using this parser.

- **Do not define variables in expression strings.** <br/> The term "parser" may lead to the assumption that one can define variables in a string passed to the parser. Something like this won't work in the intended way: <br/> `epExpression__compile("c = 2+3i", NULL, NULL);` <br/> Stick to the functions provided by the header file and implement variables in the same manner shown in the [example](#Complete-Example).

- **Be careful when evaluating complex expressions or values with the 'epExpression__eval_real' function.** <br/> Every time, when you work with complex numbers and functions that are concepted for the use of real values, the imaginary part of the complex value will be discarded, possibly leading to false results. This in particular occurs with comparison operators that are only defined for real values, meaning that an expression like `"2+3i < 3+2i"` will be evaluated to true, because the real parts on every side lead to that result during comparison. Remember: The expression does not know whether it contains complex values, the library user has to keep an eye on what is passed to compile and what will be evaluated.

- **You don't necessarily need to use the error code functionality or a variables container.** <br/> These two features are meant to ease things, but there is no immediate need to use them. While evaluating constant expressions, i. e. expressions without variables, one could simply pass NULL for the variables container parameter in the `epExpression__compile` function. The same goes for the error code. If one is not interested in where a potential error occured, just pass NULL.

- **Functions get checked before variables.** <br/> One cannot overwrite a function with a variable name.

- **Variables are assigned by reference.** <br/> A core feature of this library is the easy use of variables. During compilation, the address of a given variable is assigned, meaning that one can change the value of the used variable without the need of another compiling step.

- **Variables can be overwritten.** <br/> If a variable name already exists in the container, the address gets overwritten.

- **Powers are evaluated from right to left.** <br/> While the evaluation order of every other function or operator follows their precedence level and a left-to-right handling, powers are evaluated as follows: `4^3^2 = 4^(3^2)`. Keep that in mind or use braces to achieve a left-to-right evaluation order for powers.

- **Imaginary values get evaluated as such.** <br/> If an expression contains an imaginary value, an evaluation of such one would occur as follows: `5i = (5 * i)`, not as in `5i = 5 * i`. The difference stands out when operators with a higher precedence level act on these values: `(5 * i)^2 != 5 * i^2`. But pay attention! This only occurs on values directly followed by the imaginary unit, so: `3+4i^2 == 3 + (4i)^2` and `3+4i^2 != (3+4i)^2`.

- **Unary inverts (a.k.a. minus signs).** <br/> Even though some unary invert occurances are syntactically incorrect, this library supports some, such as a leading minus sign or a multiplicative operator followed directly by a minus.

- **Scientific notation is supported.** <br/> Only for real values and only with a leading and upcoming real value like `1e+5`, `-3e4`, `7e-5` but not `e+2`, `ie-7` nor `3e`.

- **Error codes** <br/> If you pass an argument for the error code, this number contains information that can be interpreted in the following manner:
  + Error = 0: <br/> No errors occured during compilation.
  + Error = Value between 1 and length of expression string: <br/> A function or a variable is not recognized or the expression string is not balanced, meaning that not every opening brace has a well-placed closing brace.
  + Error = -1: <br/> An error occured during the synthesis of the reverse polish notation.

## Extra: Short explenation of the project components

Following are some words about the separate components that this project consists of. In general, there is a separation between functions used solely in that specific part, those that are used among different parts and those supposed to be used by the library user. Therefore, the structure of these hierarchies is implicitly implemented as follows:

* `./include/`: <br/> Every header file found here is meant to be included by the library user.

* `./src/*/*.h`: <br/> These headers consist of functions meant to be used by the different project components.

* `./src/*/*_def.h`: <br/> These header files consist of structure definitions, most of the time meant to be kept from the project maintainer or library user to avoid direct manipulation of these structs that could bypass a specific execution order of other functions considering that structure.

Now follows a short description of the different project parts.

- **Analysis** <br/> This part contains functions that help identifying numbers and characters that occur in the expression string passed to the compilation routine.

- **Expression** <br/> This part contains the definitions behind the expression struct that gets evaluated by the library. The expression struct itself only contains the root node of the compiled math expression and serves as an abstraction layer to enable the user to only include one header file instead of multiple ones.

- **Functions** <br/> This part contains the pure math functions and some additional information about the functions such as whether the function takes one or two arguments, the precedence level of evaluation necessary for the implementation of the shunting yard algorithm and what type the input and the output are of. The header of this part can be extended, following the pattern all the other functions are listed.

- **Node** <br/> This part contains everything about the nodes that the recursive node tree contains of, the core pieces of the evaluation process.

- **Stack** <br/> This part contains the code for the stack that is needed during the application of the shunting yard algorithm.

- **Value** <br/> This part contains the definitions for the value structure that is used to store real and complex values and references which are needed during evaluation.

- **Variables** <br/> This part contains the code for the variable container that eases the variable handling in advance of the compilation process.