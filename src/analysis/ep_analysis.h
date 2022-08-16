#ifndef EP_ANALYSIS_H
#define EP_ANALYSIS_H

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

#include <complex.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

bool ep_analysis__is_numeric (char);
bool ep_analysis__is_imag_unit (char);
bool ep_analysis__is_opening_brace (char);
bool ep_analysis__is_closing_brace (char);
bool ep_analysis__is_function_char (char);

bool ep_analysis__is_brace_pair (char, char);
bool ep_analysis__is_string_balanced (const char *string, unsigned int* error);

char ep_analysis__get_complementary_brace (char);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // EP_ANALYSIS_H