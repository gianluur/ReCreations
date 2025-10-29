#include "int_to_string.h"

char *intToString(int64 number, char *buffer) {
  char digits[] = "0123456789";
  char temp[21]; // Temporary buffer with enough capacity to store 64-bit number + sign + null terminator

  // Quick return if the number is 0
  if (number == 0){
    buffer[0] = '0';
    buffer[1] = '\0';
    return buffer;
  }

  uint64 unsigned_number;
  bool isNegative = number < 0;

  if (isNegative) {
    unsigned_number = (uint64)-number; // prevents overflow
  }
  else {
    unsigned_number = (uint64)number;
  }

  // Converts the number to string rappresentation
  int i;
  for (i = 0; unsigned_number > 0; i++) {
    int remainder = unsigned_number % 10;
    temp[i] = digits[remainder];
    unsigned_number /= 10;
  }

  // Add the sign if necessary
  if (isNegative) {
    temp[i++] = '-';
  }

  // Reverse the temp buffer inside the actual buffer
  int j;
  for (j = 0; i > 0; j++) {
    buffer[j] = temp[--i];
  }

  // Add terminator and return
  buffer[j] = '\0';
  return buffer;
}