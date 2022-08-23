#ifndef EP_FUNCTIONS_H
#define EP_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <math.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

#ifndef INFINITY
#define INFINITY 1.0/0.0
#endif

#ifndef NAN
#define NAN 0.0/0.0
#endif

//-----------------------------------------------------------------------------

typedef enum eArgc {

  ONE,
  TWO

} eArgc;

//-----------------------------------------------------------------------------

typedef enum eFunction {

  RR,
  CR,
  CC

} eFunction;

//-----------------------------------------------------------------------------

typedef enum ePrecedence {

  EQ,
  Q,
  ADDITIVE,
  MULTIPLICATIVE,
  POWER,
  F

} ePrecedence;

//-----------------------------------------------------------------------------

typedef union uFunction {

  union {
    double (*_1) (double);
    double (*_2) (double, double);
  } rr;

  union {
    double (*_1) (double complex);
    double (*_2) (double complex, double complex);
  } cr;

  union {
    double complex (*_1) (double complex);
    double complex (*_2) (double complex, double complex);
  } cc;

} uFunction;

//-----------------------------------------------------------------------------

typedef struct epFunction {

  eFunction type;
  eArgc argc;
  uFunction function;

} epFunction;

//-----------------------------------------------------------------------------

double complex ep_functions_cadd (double complex a, double complex b);
double complex ep_functions_csub (double complex a, double complex b);
double complex ep_functions_cmul (double complex a, double complex b);
double complex ep_functions_cdiv (double complex a, double complex b);
double complex ep_functions_cpow (double complex a, double complex b);

double complex ep_functions_cmul_inv (double complex a, double complex b);
double complex ep_functions_cdiv_inv (double complex a, double complex b);
double complex ep_functions_cpow_inv (double complex a, double complex b);

double ep_functions_lt (double a, double b);
double ep_functions_gt (double a, double b);
double ep_functions_leq (double a, double b);
double ep_functions_geq (double a, double b);

double ep_functions_eq (double complex a, double complex b);
double ep_functions_neq (double complex a, double complex b);

double ep_functions_and (double complex a, double complex b);
double ep_functions_or (double complex a, double complex b);

double ep_functions_mod (double a, double b);
double ep_functions_mod_inv (double a, double b);

double ep_functions_scientific (double a, double b);
double ep_functions_scientific_inv (double a, double b);

//-----------------------------------------------------------------------------

typedef struct epFunctionListElement {

  const char *name;
  const void *pFunction;
  const eFunction type;
  const eArgc argc;
  const ePrecedence prec;

} epFunctionListElement;

//-----------------------------------------------------------------------------

static const epFunctionListElement epFunctionList[] = {

  {"<", ep_functions_lt, RR, TWO, Q},
  {">", ep_functions_gt, RR, TWO, Q},
  {"<=", ep_functions_leq, RR, TWO, Q},
  {"=<", ep_functions_leq, RR, TWO, Q},
  {">=", ep_functions_geq, RR, TWO, Q},
  {"=>", ep_functions_geq, RR, TWO, Q},

  {"==", ep_functions_eq, CR, TWO, EQ},
  {"!=", ep_functions_neq, CR, TWO, EQ},
  {"=!", ep_functions_neq, CR, TWO, EQ},

  {"&", ep_functions_and, CR, TWO, MULTIPLICATIVE},
  {"|", ep_functions_or, CR, TWO, ADDITIVE},

  {"%", ep_functions_mod, RR, TWO, MULTIPLICATIVE},
  {"%-", ep_functions_mod_inv, RR, TWO, MULTIPLICATIVE},

  {"+", ep_functions_cadd, CC, TWO, ADDITIVE},
  {"-", ep_functions_csub, CC, TWO, ADDITIVE},
  {"*", ep_functions_cmul, CC, TWO, MULTIPLICATIVE},
  {"/", ep_functions_cdiv, CC, TWO, MULTIPLICATIVE},
  {"^", ep_functions_cpow, CC, TWO, POWER},

  {"*-", ep_functions_cmul_inv, CC, TWO, MULTIPLICATIVE},
  {"/-", ep_functions_cdiv_inv, CC, TWO, MULTIPLICATIVE},
  {"^-", ep_functions_cpow_inv, CC, TWO, POWER},

  {"e", ep_functions_scientific, RR, TWO, F},
  {"e+", ep_functions_scientific, RR, TWO, F},
  {"e-", ep_functions_scientific_inv, RR, TWO, F},

  {"abs", cabs, CR, ONE, F},
  {"exp", cexp, CC, ONE, F},
  {"log", clog, CC, ONE, F},
  {"sqrt", csqrt, CC, ONE, F},

  {"real", creal, CR, ONE, F},
  {"imag", cimag, CR, ONE, F},
  {"arg", carg, CR, ONE, F},
  {"conj", conj, CC, ONE, F},

  {"acos", cacos, CC, ONE, F},
  {"asin", casin, CC, ONE, F},
  {"atan", catan, CC, ONE, F},

  {"cos", ccos, CC, ONE, F},
  {"sin", csin, CC, ONE, F},
  {"tan", ctan, CC, ONE, F},

  {"sinh", csinh, CC, ONE, F},
  {"cosh", ccosh, CC, ONE, F},
  {"tanh", ctanh, CC, ONE, F},

  {"asinh", casinh, CC, ONE, F},
  {"acosh", cacosh, CC, ONE, F},
  {"atanh", catanh, CC, ONE, F}
};

//-----------------------------------------------------------------------------

int
ep_functions__exists_at (
  const char *name
);

bool
ep_functions__exists (
  const char *name
);

bool
ep_functions__is_unary_invert (
  const char *name
);

bool
ep_functions__has_right_to_left_precedence (
  const epFunctionListElement const *function
);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_FUNCTIONS_H