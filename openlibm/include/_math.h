#ifndef  _MATH_H_
#define  _MATH_H_

#include <openlibm_math.h>

#if !defined(FLT_EVAL_METHOD) && defined(__FLT_EVAL_METHOD__)
  #define FLT_EVAL_METHOD __FLT_EVAL_METHOD__
  #define __TMP_FLT_EVAL_METHOD
#endif /* FLT_EVAL_METHOD */
#if defined FLT_EVAL_METHOD
  #if FLT_EVAL_METHOD == 0
    typedef float  float_t;
    typedef double double_t;
   #elif FLT_EVAL_METHOD == 1
    typedef double float_t;
    typedef double double_t;
   #elif FLT_EVAL_METHOD == 2
    typedef long double float_t;
    typedef long double double_t;
   #else
    /* Implementation-defined.  Assume float_t and double_t have been
     * defined previously for this configuration (e.g. config.h). */
  #endif
#else
    /* Assume basic definitions.  */
    typedef float  float_t;
    typedef double double_t;
#endif
#if defined(__TMP_FLT_EVAL_METHOD)
  #undef FLT_EVAL_METHOD
#endif

#endif
