// @file memory.hpp

#pragma once

#include "utilities/types.h"

// @brief Memory management & Memory manipulation
namespace memory {

    // === Memory Management ===
    void *allocate(const uint64 size);
    void *reallocate(void *ptr, const uint64 size);
    void *cleaned_allocate(const uint64 count, const uint64 size);
    void deallocate(void *ptr);

    // === Memory Manipulation ===
    void *copy(void* dest, const void* src, const uint64 size);
    void *move(void *dest, const void *src, const uint64 size);
    void *set(void *dest, const void *src, const uint64 size);
    bool compare(const void *s1, const void *s2, const uint64 size);
    bool find(const void *s, const void *c, const uint64 size);

}; // namespace memory