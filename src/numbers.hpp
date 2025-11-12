// @file numbers.hpp

#pragma once

#include "utilities/types.h"

// === Limits of various type ===

template <typename T>
struct limits;

template <>
struct limits<int8> {
    static constexpr int8 min() { return INT8_MIN; }
    static constexpr int8 max() { return INT8_MAX; }
};

template <>
struct limits<int16> {
    static constexpr int16 min() { return INT16_MIN; }
    static constexpr int16 max() { return INT16_MAX; }
};

template <>
struct limits<int32> {
    static constexpr int32 min() { return INT32_MIN; }
    static constexpr int32 max() { return INT32_MAX; }
};

template <>
struct limits<int64> {
    static constexpr int64 min() { return INT64_MIN; }
    static constexpr int64 max() { return INT64_MAX; }
};

template <>
struct limits<uint8> {
    static constexpr uint8 min() { return UINT8_MIN; }
    static constexpr uint8 max() { return UINT8_MAX; }
};

template <>
struct limits<uint16> {
    static constexpr uint16 min() { return UINT16_MIN; }
    static constexpr uint16 max() { return UINT16_MAX; }
};

template <>
struct limits<uint32> {
    static constexpr uint32 min() { return UINT32_MIN; }
    static constexpr uint32 max() { return UINT32_MAX; }
};

template <>
struct limits<uint64> {
    static constexpr uint64 min() { return UINT64_MIN; }
    static constexpr uint64 max() { return UINT64_MAX; }
};

template <>
struct limits<float32> {
    static constexpr float32 min() { return FLOAT32_MIN; }
    static constexpr float32 max() { return FLOAT32_MAX; }
};

template <>
struct limits<float64> {
    static constexpr float64 min() { return FLOAT64_MIN; }
    static constexpr float64 max() { return FLOAT64_MAX; }
};

// === Signed type trait ===
template <typename T>
struct isSigned {
    static constexpr bool value = false;
};

template <> struct isSigned<int8> {
    static constexpr bool value = true;
};

template <> struct isSigned<int16> {
    static constexpr bool value = true;
};

template <> struct isSigned<int32> {
    static constexpr bool value = true;
};

template <> struct isSigned<int64> {
    static constexpr bool value = true;
};

// === Integer type trait ===

template <typename T>
struct isInteger {
    static constexpr bool value = false;
};

// === Specializations for signed integer types ===
template <> struct isInteger<int8> {
    static constexpr bool value = true;
};

template <> struct isInteger<int16> {
    static constexpr bool value = true;
};

template <> struct isInteger<int32> {
    static constexpr bool value = true;
};

template <> struct isInteger<int64> {
    static constexpr bool value = true;
};

// === Specializations for unsigned integer types ===

template <> struct isInteger<uint8> {
    static constexpr bool value = true;
};

template <> struct isInteger<uint16> {
    static constexpr bool value = true;
};

template <> struct isInteger<uint32> {
    static constexpr bool value = true;
};

template <> struct isInteger<uint64> {
    static constexpr bool value = true;
};

// === Floating type trait ===

template <typename T>
struct isFloatingPoint {
    static constexpr bool value = false;
};

template <> struct isFloatingPoint<float32> {
    static constexpr bool value = true;
};

template <> struct isFloatingPoint<float64> {
    static constexpr bool value = true;
};
