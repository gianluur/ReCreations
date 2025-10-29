#include "decimal_to_string.h"

// This functions needs a buffer of atleast 128 bytes
char* decimalToString(double number, int precision, char* buffer) {
  char* ptr = buffer;
  
  // Max size for 64-bit int part is 21 (sign + 19 digits + null terminator)
  char intBuffer[21]; 

  // Add the sign if necessary
  if (number < 0) {
    *ptr++ = '-';
    number = -number; 
  }
  
  // Calculating the interger part
  long long intPart = (long long)number;
  intToString(intPart, intBuffer);
  
  // Copy the integer string into the main buffer
  char* intStr = intBuffer;
  while (*intStr) {
    *ptr++ = *intStr++;
  }

  // Calculating the floating point part
  if (precision > 0) {
    *ptr++ = '.';
    
    double fracPart = number - (double)intPart;
    double roundingFactor = 0.5;
    for (int i = 0; i < precision; ++i) {
      roundingFactor /= 10.0;
    }
    
    fracPart += roundingFactor; 

    // Extract and append the digits
    for (int i = 0; i < precision; ++i) {
      fracPart *= 10;
      
      // Truncate the digit (Example, if fracPart is 7.9, fracInt is 7)
      int fracInt = (int)fracPart;
      
      // Append the digit
      *ptr++ = '0' + fracInt;
      
      // Remove the digit we just used (Example, 7.9 - 7 = 0.9)
      fracPart -= fracInt; 
    }
  }

  // Add NULL terminator and return
  *ptr = '\0';
  return buffer;
}