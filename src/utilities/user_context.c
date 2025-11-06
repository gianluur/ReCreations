#include "user_context.h"
#include "converters/int_to_string/int_to_string.h"

#if defined(COMPILER_MSVC)
static void build_msvc_version(char *buffer, int full_ver) {
  int major = 0, minor = 0, patch = 0;

  if (full_ver >= 100000000) { // 9 digits
      major = full_ver / 10000000;
      minor = (full_ver / 100000) % 100;
      patch = full_ver % 100000;
  } else { // 8 digits
      major = full_ver / 1000000;
      minor = (full_ver / 10000) % 100;
      patch = full_ver % 10000;
  }

  char major_buf[12];
  char minor_buf[12];
  char patch_buf[12];

  if (!intToString(major, major_buf) ||
      !intToString(minor, minor_buf) ||
      !intToString(patch, patch_buf)) 
  {
      if (buffer) buffer[0] = '\0';
      return;
  }

  // Build final string: "major.minor.patch"
  int k = 0, i = 0;
  // Now you iterate directly over the arrays starting at index 0
  for (i = 0; major_buf[i]; ++i) buffer[k++] = major_buf[i];
  buffer[k++] = '.';
  for (i = 0; minor_buf[i]; ++i) buffer[k++] = minor_buf[i];
  buffer[k++] = '.';
  for (i = 0; patch_buf[i]; ++i) buffer[k++] = patch_buf[i];
  buffer[k] = '\0';

}

#endif

UserContext getUserContext() {
  const UserContext context = {
    .os = OS_NAME,
    .architecture = ARCHITECTURE_NAME,
    .compiler = COMPILER_NAME,
    
    #if defined(COMPILER_MSVC)
      #if defined(_MSC_FULL_VER)
        build_msvc_version(context.compiler_version, _MSC_FULL_VER);
      #else 
        build_msvc_version(context.compiler_version, _MSC_VER * 10000);
      #endif
    #else
      .compiler_version = COMPILER_VERSION
    #endif
  };

  return context;
}

