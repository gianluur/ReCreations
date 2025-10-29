#include "string_to_int.h"

int stringToInt(const char* str, const int length){
  int number = 0;
  
  for(int i = 0; i < length; i++)
    number += (str[i] - '0') * (int)pow(10, length - i - 1);
  return number;
}