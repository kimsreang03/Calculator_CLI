#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/scanner.h"
#include "../include/calculator.h"
#include "../include/callib.h"

void calculator(char* input){

  short constant_size = 0, operator_size = 0, i = 0, j = 0;


  // get the size(amount) of constant and operator
  Scanner* _scanner = init_scanner(input);
  Element* _element = 0;
  while((_element = scanner_next_element(_scanner))->type !=EOI){
    if(_element->type == CONSTANT) constant_size++;
    else if(_element->type != CONSTANT) operator_size++;
    free(_element->value);
    free(_element);
  }
  free(_scanner);
  free(_element);

  float* constant = calloc(constant_size, sizeof(float)); // allocate for constant
  short* operator = calloc(operator_size, sizeof(short)); // allocate for operator

  //scan and get elements from input
  Scanner* scanner = init_scanner(input);
  Element* element = 0;
  while((element= scanner_next_element(scanner))->type != EOI){
    //check if element is not constant
    if(element->type != CONSTANT){
      if(j < operator_size){
        operator[j] = element->type;
        j++;
      }
    }else{ // if element is constant
      if(i < constant_size){
        // convert from string to float data_type and put it in constant[]
        constant[i] = conevert_to_constant(element->value);
        i++;
      }
    }
    free(element->value);
    free(element);
  }
  free(scanner);
  free(element);


  float result = calculate_arithmetic(constant, operator, constant_size, operator_size);

  printf("the result is %f\n", result);

  free(constant);
  free(operator);
}



float calculate_arithmetic(float* constant, const short* operator, const short constant_size, const short operator_size){

  // for(int i = 0; i < constant_size; i++){
  //   printf("number: %f\n", constant[i]);
  // }
  // for(int i = 0; i < operator_size; i++){
  //   printf("operator: %d\n", operator[i]);
  // }

  // + - * / 1 2 3` 4`

  float result = 0;
  bool noMultiDivide = false;

  for(int i = 1; i <= 4; i++){
      if(operator[i] != MULTIPLY_SIGN || operator[i] != DIVIDE_SIGN)
        noMultiDivide = true;
  }
  if(noMultiDivide){
    short i;
    for( i = 0; i < operator_size; i++){

        if(operator[i] == PLUS_SIGN) constant[i+1] = constant[i] + constant[i+1];
        if(operator[i] == MINUS_SIGN) constant[i+1] = constant[i] - constant[i+1];

    }
    result = constant[i];
  }


  return result;
}
