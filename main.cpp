#include "Recreation.h"
#include <cstdio>

#include "integers.hpp"
#include "numbers.hpp"

int main(void) {

    int8 a = limits<int8>::min();
    printf("LIMIT: %d\n", a);
    
    a += 1;
    printf("POST: %d\n", a);

    return 0;
}
