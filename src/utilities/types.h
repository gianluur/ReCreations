#include "compiler.h"
#include "os.h"

#ifndef TYPES_H
  #define TYPES_H

  #if defined(COMPILER_CLANG) || defined(COMPILER_GCC)
    #define typeof(type) __typeof__(type)
  #elif defined(COMPILER_MSVC)
    #define typeof(type) decltype(type)
  #endif

  typedef unsigned char byte;

  typedef unsigned char uint8;
  typedef unsigned short uint16;
  typedef unsigned int uint32;
  typedef unsigned long long uint64;

  typedef signed char int8;
  typedef signed short int16;
  typedef signed int int32;
  typedef signed long long int64;

  #ifndef __cplusplus
    typedef unsigned char bool;
    #define true 1
    #define false 0
  #endif

  #ifndef NULL
    #define NULL ((void *)0)
  #endif

  #define UINT8_MIN 0U
  #define UINT8_MAX 255U

  #define UINT16_MIN 0U
  #define UINT16_MAX 65535U

  #define UINT32_MIN 0U
  #define UINT32_MAX 4294967295U

  #define UINT64_MIN 0ULL
  #define UINT64_MAX 18446744073709551615ULL

  #define INT8_MIN -128
  #define INT8_MAX 127

  #define INT16_MIN -32768
  #define INT16_MAX 32767

  #define INT32_MIN -2147483648
  #define INT32_MAX 2147483647

  #define INT64_MIN -9223372036854775807LL
  #define INT64_MAX 9223372036854775807LL

#endif