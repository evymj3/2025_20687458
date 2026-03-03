#ifndef ADDER_H
#define ADDER_H

// The PDF mentions a definition for static/shared; this ensures it works
#ifdef maths_STATIC
#define MATHSLIB_API
#else
#define MATHSLIB_API
#endif

MATHSLIB_API int add(int a, int b);

#endif