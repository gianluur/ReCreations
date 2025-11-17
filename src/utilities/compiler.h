#ifndef COMPILER_H
#define COMPILER_H

// ============================================================================
//  Unified Compiler Version Utilities
//  V = Version, R = Revision, P = Patch
//  Only Microsoft will not abide this because they use a different format
// ============================================================================

#define COMPILER_NORMALIZED_VERSION(v, r, p) (((v) << 24) + ((r) << 16) + (p))

// Transforms the version into a human-readable string
#define COMPILER_STRING_VERSION(v, r, p) #v "." #r "." #p

// Required because the compiler doesn't expand macro arguments inside
// stringification
#define COMPILER_EXPAND_STRING(v, r, p) COMPILER_STRING_VERSION(v, r, p)
#define NORMALIZED_VERSION(v, r, p) COMPILER_NORMALIZED_VERSION(v, r, p)

// Compare compilers versions
// Example: #if COMPILER_VERSION_IS_ATLEAST(COMPILER_GCC, 6, 0, 0)
#define COMPILER_VERSION_IS_ATLEAST(compiler_name, v, r, p) \
  (defined(compiler_name) &&                                \
   COMPILER_VERSION_NORMALIZED >= COMPILER_NORMALIZED_VERSION(v, r, p))

#if defined(_MSC_VER)

#define COMPILER_MSVC
#define COMPILER_NAME "MSVC"

#if defined(_MSC_FULL_VER)
// VS 2017+ (9 digits): VVRRPPPPP
#if _MSC_FULL_VER >= 100000000
#define COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
#define COMPILER_VERSION_MINOR ((_MSC_FULL_VER / 100000) % 100)
#define COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)

// VS <= 2015 (8 digits): VVRRPPPP
#else
#define COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
#define COMPILER_VERSION_MINOR ((_MSC_FULL_VER / 10000) % 100)
#define COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)

#endif

// Optional build number (from Visual C++ 2008+)
#if defined(_MSC_BUILD)
#define COMPILER_VERSION_BUILD _MSC_BUILD

#else
#define COMPILER_VERSION_BUILD 0
#endif

#else  // Only _MSC_VER is defined (very old MSVC)
#define COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#define COMPILER_VERSION_MINOR (_MSC_VER % 100)
#define COMPILER_VERSION_PATCH 0
#define COMPILER_VERSION_BUILD 0
#endif

#define COMPILER_VERSION_NORMALIZED                                  \
  NORMALIZED_VERSION(COMPILER_VERSION_MAJOR, COMPILER_VERSION_MINOR, \
                     COMPILER_VERSION_PATCH)

#define COMPILER_VERSION                                                 \
  COMPILER_EXPAND_STRING(COMPILER_VERSION_MAJOR, COMPILER_VERSION_MINOR, \
                         COMPILER_VERSION_PATCH)

#elif defined(__clang__)
#define COMPILER_CLANG
#define COMPILER_NAME "Clang"
#define COMPILER_VERSION_NORMALIZED \
  NORMALIZED_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#define COMPILER_VERSION \
  COMPILER_EXPAND_STRING(__clang_major__, __clang_minor__, __clang_patchlevel__)

#elif defined(__GNUC__)
#define COMPILER_GCC
#define COMPILER_NAME "GCC"

#if defined(__GNUC_PATCHLEVEL__)
#define COMPILER_VERSION_NORMALIZED \
  NORMALIZED_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#define COMPILER_VERSION \
  COMPILER_EXPAND_STRING(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)

#else
#define COMPILER_VERSION_NORMALIZED \
  NORMALIZED_VERSION(__GNUC__, __GNUC_MINOR__, 0)
#define COMPILER_VERSION COMPILER_EXPAND_STRING(__GNUC__, __GNUC_MINOR__, 0)
#endif

#else
#define COMPILER_UNKNOWN
#define COMPILER_NAME "Unknown"
#define COMPILER_VERSION_NORMALIZED 0
#define COMPILER_VERSION "0.0.0"
#endif

#endif
