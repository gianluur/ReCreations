#include "Recreation.h"
#include "memory/memory.hpp"

#include <cstdio>

int main(void) {

    void *test = memory::allocate(10);
    printf("%p\n", test);

    return 0;
}
