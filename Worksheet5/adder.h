#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H

/** @file
 * This file contains the declarations of all exported functions in the maths library.
 */

#if defined(_WIN32) || defined(WIN32)
  #ifdef maths_STATIC
    #define MATHSLIB_API
  #else
    #ifdef maths_EXPORTS
      #define MATHSLIB_API __declspec(dllexport)
    #else
      #define MATHSLIB_API __declspec(dllimport)
    #endif
  #endif
#else
  #define MATHSLIB_API
#endif

/** Adding function [Brief description]
 * This function adds two numbers [More detail]
 * @param a is the first number [Parameter definition]
 * @param b is the second number [Parameter definition]
 * @return sum of a and b [Return value description]
 */
MATHSLIB_API int add(int a, int b);

#endif