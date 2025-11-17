// @file numbers.hpp

#pragma once

#include "utilities/types.h"

// === Limits of various type ===

template <typename T>
struct limits;

template <>
struct limits<int8> {
  static constexpr int8 min = INT8_MIN;
  static constexpr int8 max = INT8_MAX;
};

template <>
struct limits<int16> {
  static constexpr int16 min = INT16_MIN;
  static constexpr int16 max = INT16_MAX;
};

template <>
struct limits<int32> {
  static constexpr int32 min = INT32_MIN;
  static constexpr int32 max = INT32_MAX;
};

template <>
struct limits<int64> {
  static constexpr int64 min = INT64_MIN;
  static constexpr int64 max = INT64_MAX;
};

template <>
struct limits<uint8> {
  static constexpr uint8 min = UINT8_MIN;
  static constexpr uint8 max = UINT8_MAX;
};

template <>
struct limits<uint16> {
  static constexpr uint16 min = UINT16_MIN;
  static constexpr uint16 max = UINT16_MAX;
};

template <>
struct limits<uint32> {
  static constexpr uint32 min = UINT32_MIN;
  static constexpr uint32 max = UINT32_MAX;
};

template <>
struct limits<uint64> {
  static constexpr uint64 min = UINT64_MIN;
  static constexpr uint64 max = UINT64_MAX;
};

template <>
struct limits<float32> {
  static constexpr float32 min = FLOAT32_MIN;
  static constexpr float32 max = FLOAT32_MAX;
};

template <>
struct limits<float64> {
  static constexpr float64 min = FLOAT64_MIN;
  static constexpr float64 max = FLOAT64_MAX;
};

// === Signed type trait ===
template <typename T>
struct isSigned {
  static constexpr bool value = false;
};

template <>
struct isSigned<int8> {
  static constexpr bool value = true;
};

template <>
struct isSigned<int16> {
  static constexpr bool value = true;
};

template <>
struct isSigned<int32> {
  static constexpr bool value = true;
};

template <>
struct isSigned<int64> {
  static constexpr bool value = true;
};

// === Integer type trait ===

template <typename T>
struct isInteger {
  static constexpr bool value = false;
};

// === Specializations for signed integer types ===
template <>
struct isInteger<int8> {
  static constexpr bool value = true;
};

template <>
struct isInteger<int16> {
  static constexpr bool value = true;
};

template <>
struct isInteger<int32> {
  static constexpr bool value = true;
};

template <>
struct isInteger<int64> {
  static constexpr bool value = true;
};

// === Specializations for unsigned integer types ===

template <>
struct isInteger<uint8> {
  static constexpr bool value = true;
};

template <>
struct isInteger<uint16> {
  static constexpr bool value = true;
};

template <>
struct isInteger<uint32> {
  static constexpr bool value = true;
};

template <>
struct isInteger<uint64> {
  static constexpr bool value = true;
};

// === Floating type trait ===

template <typename T>
struct isFloatingPoint {
  static constexpr bool value = false;
};

template <>
struct isFloatingPoint<float32> {
  static constexpr bool value = true;
};

template <>
struct isFloatingPoint<float64> {
  static constexpr bool value = true;
};

template <typename T>
concept Integer = isInteger<T>::value;

template <typename T>
concept FloatingPoint = isFloatingPoint<T>::value;