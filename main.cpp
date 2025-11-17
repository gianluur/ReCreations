#include <cstdio>

#include "Recreation.h"

int64 test2() { return INT64_MAX; }

int32 test() { return INT32_MAX + test2(); }

int32 main(void) {
  int8 x = INT8_MAX + test();
  printf("%d", x);
  return 0;
}
