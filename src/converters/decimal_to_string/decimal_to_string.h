#ifndef DECIMAL_TO_STRING_H
  #define DECIMAL_TO_STRING_H

  #include "utilities/types.h"
  #include "converters/int_to_string/int_to_string.h"
  
  char* decimalToString(double number, int precision, char* buffer);

#endif