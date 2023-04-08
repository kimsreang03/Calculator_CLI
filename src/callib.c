#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../include/callib.h"

float conevert_to_constant(const char* value){

  float constant = 0;
  int i = 0, str_value = strlen(value);
  int digit, fraction_part, point = 0;
  bool isDecimal = false;

  while(i < str_value && value[i] != '\0'){

    switch (value[i]) {
      case 48: digit = 0; break;
      case 49: digit = 1; break;
      case 50: digit = 2; break;
      case 51: digit = 3; break;
      case 52: digit = 4; break;
      case 53: digit = 5; break;
      case 54: digit = 6; break;
      case 55: digit = 7; break;
      case 56: digit = 8; break;
      case 57: digit = 9; break;
      case '.': {
        point++; //get the size of '.'
        for(int j = i + 1; j < str_value; j++, fraction_part++);
      }
      break;
      default: printf("unexpected character\n");  break;
    }
    if(value[i] == '.')
      if(point == 1) isDecimal = true; // if the value only has one '.' then it is Decimal number
      else { // if it has '.' more than one tell the user it is not a constant or number
        printf("unexpected value:  `%s` ", value);
        return 1;
      }
    else // if it is a constant
      constant = constant*10 + digit;
    i++;
  }
  if(isDecimal) constant = constant/(pow(10, fraction_part));

  return constant;

}
