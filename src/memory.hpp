// @file memory.hpp

#pragma once

#include "utilities/types.h"

// The standard library functions are only included if not in RECREATIONS_ONLY mode.
#ifndef RECREATIONS_ONLY
    #include <cstdlib> // For malloc, free, realloc, calloc
    #include <cstring> // For memcpy, memmove, memset, memcmp
#endif

// @brief Provides fundamental memory management (allocation/deallocation) and manipulation utilities, 
// often mirroring standard C library functions.
namespace memory {

    // === Memory Management (Declaration) ===

    // @brief Allocates a block of memory of a specified size.
    // @param size The number of bytes to allocate.
    // @return A pointer to the allocated memory block, or nullptr if allocation fails.
    void* allocate(const uint64 size);

    // @brief Changes the size of the memory block pointed to by ptr.
    // @param ptr Pointer to the memory block previously allocated by allocate or reallocate.
    // @param size The new size in bytes for the memory block.
    // @return A pointer to the newly allocated/reallocated memory block, or nullptr if reallocation fails.
    void* reallocate(void* ptr, const uint64 size);

    // @brief Allocates and zeroes out an array in memory.
    // @param count The number of elements to allocate.
    // @param size The size in bytes of each element.
    // @return A pointer to the allocated memory, or nullptr if allocation fails.
    void* cleaned_allocate(const uint64 count, const uint64 size);

    // @brief Deallocates the memory block pointed to by ptr.
    // @param ptr Pointer to the memory block to be freed.
    void deallocate(void* ptr);

    // === Memory Manipulation (Declaration) ===

    // @brief Copies a block of memory from a source to a destination.
    // @param dest Pointer to the destination array where the content is to be copied.
    // @param src Pointer to the source of data to be copied.
    // @param size The number of bytes to copy.
    // @return A pointer to the destination (dest).
    void* copy(void* dest, const void* src, const uint64 size);

    // @brief Copies a block of memory from a source to a destination, safely handling overlapping blocks.
    // @param dest Pointer to the destination array.
    // @param src Pointer to the source of data.
    // @param size The number of bytes to copy.
    // @return A pointer to the destination (dest).
    void* move(void* dest, const void* src, const uint64 size);

    // @brief Fills a block of memory with a specific byte value.
    // @param dest Pointer to the block of memory to fill.
    // @param src Pointer to the value used to fill the memory block (only the first byte is used).
    // @param size The number of bytes to be set to the specified value.
    // @return A pointer to the memory area dest.
    void* set(void* dest, const void* src, const uint64 size);

    // @brief Compares two blocks of memory.
    // @param s1 Pointer to the first block of memory.
    // @param s2 Pointer to the second block of memory.
    // @param size The number of bytes to compare.
    // @return true if the blocks are identical (all size bytes match), false otherwise.
    bool compare(const void* s1, const void* s2, const uint64 size);

    // @brief Checks if two blocks of memory are identical (alias for compare).
    // @param s Pointer to the first block of memory.
    // @param c Pointer to the second block of memory.
    // @param size The number of bytes to compare.
    // @return true if the blocks are identical, false otherwise.
    bool find(const void* s, const void* c, const uint64 size);

    // === Ownership Transfer (Declaration) ===

    // @brief Performs an unconditional cast to an rvalue reference, enabling move semantics.
    // @param t The object reference to be "moved" from.
    // @return An rvalue reference to the object.
    template <typename T>
    T&& pass_ownership(T& t) noexcept;
}

// === Implementation of Namespace memory ===

// Note: Since all functions are declared inline, their definitions must be provided here in the header file.

inline void* memory::allocate(const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Allocate the requested number of bytes using the standard library.
    return malloc(size);
#else
    // In recreation mode, always return null.
    return nullptr;
#endif
}

inline void* memory::reallocate(void* ptr, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Reallocate the memory block to the new size.
    return realloc(ptr, size);
#else
    // In recreation mode, always return null.
    return nullptr;
#endif
}

inline void* memory::cleaned_allocate(const uint64 count, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Allocate memory for count elements, each of size, and initialize to zero.
    return calloc(count, size);
#else
    // In recreation mode, always return null.
    return nullptr;
#endif
}

inline void memory::deallocate(void* ptr) {
#ifndef RECREATIONS_ONLY
    // Free the previously allocated memory block.
    free(ptr);
#endif
    // No operation in recreation mode.
}

inline void* memory::copy(void* dest, const void* src, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Copy bytes from src to dest. Behavior is undefined if memory blocks overlap.
    return memcpy(dest, src, size);
#else
    // In recreation mode, return null.
    return nullptr;
#endif
}

inline void* memory::move(void* dest, const void* src, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Copy bytes from src to dest, handling potential overlap between the memory blocks.
    return memmove(dest, src, size);
#else
    // In recreation mode, return null.
    return nullptr;
#endif
}

inline void* memory::set(void* dest, const void* src, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Fill the memory block with the byte value extracted from src.
    return memset(dest, *((const unsigned char*)src), size);
#else
    // In recreation mode, return null.
    return nullptr;
#endif
}

inline bool memory::compare(const void* s1, const void* s2, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Compare the specified number of bytes. Return true if they are identical (result is zero).
    return memcmp(s1, s2, size) == 0;
#else
    // In recreation mode, return false.
    return false;
#endif
}

inline bool memory::find(const void* s, const void* c, const uint64 size) {
#ifndef RECREATIONS_ONLY
    // Compare the specified number of bytes (alias for memcmp == 0).
    return memcmp(s, c, size) == 0;
#else
    // In recreation mode, return false.
    return false;
#endif
}

template <typename T>
inline T&& memory::pass_ownership(T& t) noexcept {
    // Cast an lvalue reference to an rvalue reference to enable moving the object's resources.
    return static_cast<T&&>(t);
}