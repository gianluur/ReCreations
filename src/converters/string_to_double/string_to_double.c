#include "string_to_double.h"

double stringToDouble(const char *str, const int length) {
  int isDecimal = 0;
  
  int intpart = 0; double decimalpart = 0;
  int icounter = 0, dcounter = 0;

  for(int i = 0; i < length; i++){
    if (str[i] == '.'){
      isDecimal = 1;
      continue;
    }
  
    if (!isDecimal) {
      intpart = intpart * 10 + (str[i] - '0');
      icounter++;
    }
      
    else { 
      decimalpart += (str[i] - '0') * pow(10, -(dcounter));
      dcounter++;
    }
  }
  return intpart + decimalpart / 10;
}