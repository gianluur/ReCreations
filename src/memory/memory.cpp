// @file memory.cpp

#include "memory.hpp"

#ifndef RECREATIONS_ONLY
    #include <cstdlib>
    #include <cstring>
#endif

void *memory::allocate(const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return malloc(size);
    #endif
}

void *memory::reallocate(void *ptr, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return realloc(ptr, size);
    #endif
}

void *memory::cleaned_allocate(const uint64 count, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return calloc(count, size);
    #endif
}

void memory::deallocate(void *ptr) {
    #ifndef RECREATIONS_ONLY
        free(ptr);
    #endif
}

void *memory::copy(void* dest, const void* src, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return memcpy(dest, src, size);
    #endif
}

void *memory::move(void *dest, const void *src, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return memmove(dest, src, size);
    #endif
}

void *memory::set(void *dest, const void *src, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return memset(dest, *((const unsigned char*)src), size);
    #endif
}

bool memory::compare(const void *s1, const void *s2, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return memcmp(s1, s2, size) == 0;
    #endif
}

bool memory::find(const void *s, const void *c, const uint64 size) {
    #ifndef RECREATIONS_ONLY
        return memcmp(s, c, size) == 0;
    #endif
}