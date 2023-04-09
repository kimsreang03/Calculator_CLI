#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/scanner.h"
#include "../include/calculator.h"
#include "../include/callib.h"

void calculator(char* input){

  short constant_size = 0, operator_size = 0;


  float* constant = NULL;
  short* operator = NULL;

  //scan and get elements from input
  Scanner* scanner = init_scanner(input);
  Element* element = 0;
  while((element= scanner_next_element(scanner))->type != EOI){
    //check if element is not constant
    if(element->type != CONSTANT){
        operator = realloc(operator, (operator_size+1) * sizeof(short));
        operator[operator_size] = element->type;
        operator_size++;
      } else{ // if element is constant
        constant = realloc(constant, (constant_size+1) * sizeof(float));
        constant[constant_size] = conevert_to_constant(element->value);
        constant_size++;
    }
    free(element->value);
    free(element);
  }

  free(scanner);
  free(element);

  for(int i = 0; i < constant_size; i++){
   printf("_number_: %f\n", constant[i]);
 }
 for(int i = 0; i < operator_size; i++){
   printf("_operator_: %d\n", operator[i]);
 }

  float result = calculate_arithmetic(constant, operator,constant_size, operator_size);

  free(constant);
  free(operator);
}


float calculate_arithmetic(float* constant, const short* operator, short constant_size, short operator_size){



  // + - * / 1 2 3` 4`

  float result = 0;

  short i = 0;
  float* newConstant = NULL;
  while(i < operator_size){
    printf("operator: %d\n", operator[0]);
    if(operator[i] == MULTIPLY_SIGN || operator[i] == DIVIDE_SIGN){

      while(operator[i] == MULTIPLY_SIGN || operator[i] == DIVIDE_SIGN){
        if(operator[i] == MULTIPLY_SIGN) constant[i+1] = constant[i] * constant[i+1];
        if(operator[i] == DIVIDE_SIGN) constant[i+1] = constant[i] / constant[i+1];
        i++;
        printf("constant: %f\n", constant[i+1]);
      }
      newConstant = realloc(newConstant, (i+1)*sizeof(float));
      newConstant[i] = constant[i+1];
    }else{
      printf("yr\n");
      newConstant = realloc(newConstant, (i+1)*sizeof(float));
      newConstant[i] = constant[i];

    }
    i++;
  }
  newConstant = realloc(newConstant, (i+1)*sizeof(float));
  newConstant[i] = constant[i];


  for(int a = 0; a < i + 1; a++){
    printf("%f\n",newConstant[a]);
  }
  return result;
}
