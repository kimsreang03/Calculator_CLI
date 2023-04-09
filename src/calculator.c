#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/scanner.h"
#include "../include/calculator.h"
#include "../include/callib.h"

void calculator(char* input){

  short i = 0, j = 0;


  float* constant = NULL;
  short* operator = NULL;

  //scan and get elements from input
  Scanner* scanner = init_scanner(input);
  Element* element = 0;
  while((element= scanner_next_element(scanner))->type != EOI){
    //check if element is not constant
    if(element->type != CONSTANT){
        operator = realloc(operator, (j+1) * sizeof(short));
        operator[j] = element->type;
        j++;
      } else{ // if element is constant
        constant = realloc(constant, (i+1) * sizeof(float));
        constant[i] = conevert_to_constant(element->value);
        i++;
    }
    free(element->value);
    free(element);
  }

  free(scanner);
  free(element);


  free(constant);
  free(operator);
}


float calculate_arithmetic(float* constant, const short* operator){

  // for(int i = 0; i < constant_size; i++){
  //   printf("number: %f\n", constant[i]);
  // }
  // for(int i = 0; i < operator_size; i++){
  //   printf("operator: %d\n", operator[i]);
  // }

  // + - * / 1 2 3` 4`

  float result = 0;
  short constant_size = sizeof(constant)/sizeof(float);
  short operator_size = sizeof(operator)/sizeof(short);
  short i = 0;
  float* newConstant = NULL;
  while(i < operator_size){
    if(operator[i] != MULTIPLY_SIGN || operator[i] != DIVIDE_SIGN){
      newConstant = realloc(newConstant, (i+1)*sizeof(float));
      newConstant[i] = constant[i];
    }else if(operator[i] == MULTIPLY_SIGN || operator[i] == DIVIDE_SIGN){
      newConstant = realloc(newConstant, (i+1)*sizeof(float));
      if(operator[i] == MULTIPLY_SIGN) constant[i+1] = constant[i] * constant[i+1];
      if(operator[i] == DIVIDE_SIGN) constant[i+1] = constant[i] / constant[i+1];

      while(operator[i+1] == MULTIPLY_SIGN || operator[i+1] == DIVIDE_SIGN){
        if(operator[i] == MULTIPLY_SIGN) constant[i+1] = constant[i] * constant[i+1];
        if(operator[i] == DIVIDE_SIGN) constant[i+1] = constant[i] / constant[i+1];
        i++;
      }
      newConstant[i] = constant[i+1];
    }
    i++;

  }

  for(int i = 0, str = sizeof(newConstant)/sizeof(float); i < str; i++){
    printf("%f\n",newConstant[i]);
  }
  return result;
}
