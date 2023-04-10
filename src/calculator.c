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
   printf("operator_: %d\n", operator[i]);
 }
 printf("\n\n");

  float result = calculate_arithmetic(constant, operator,constant_size, operator_size);

  printf("the result is %f\n\n", result);

  free(constant);
  free(operator);
}


float calculate_arithmetic(float* constant, short* operator, short constant_size, short operator_size){

  // + - * / 1 2 3` 4`

  float result = 0;

  bool hasPlusMinus = false;

  for(short i = 0; i < operator_size; i++){
    if(operator[i] == PLUS_SIGN || operator[i] == MINUS_SIGN)
      hasPlusMinus = true;
  }

  if(operator_size == constant_size - 1 && hasPlusMinus){

    int i = 0;
    float* new_constant = calloc(0, sizeof(float));
    short* new_operater = calloc(0, sizeof(short));
    short new_operater_size = 0;
    short new_constant_size = 0;
    short skipped = 0;



    while(i < operator_size){

      if(operator[i-skipped] == PLUS_SIGN || operator[i-skipped] == MINUS_SIGN){
        // copy the plus_sign and minus_sign into new array
        new_operater = realloc(new_operater, (i+1-skipped)*sizeof(short));
        new_operater[i-skipped] = operator[i-skipped];
        new_operater_size++;

        new_constant = realloc(new_constant, (i+1-skipped)*sizeof(float));
        new_constant[i-skipped] = constant[i-skipped];
        new_constant_size++;
        i++;
      }
      if(operator[i-skipped] == MULTIPLY_SIGN || operator[i-skipped] == DIVIDE_SIGN){
        while(operator[i-skipped] == MULTIPLY_SIGN || operator[i-skipped] == DIVIDE_SIGN){

          if(operator[i-skipped] == MULTIPLY_SIGN)
            constant[i+1-skipped] = constant[i-skipped] * constant[i+1-skipped];
          if(operator[i-skipped] == DIVIDE_SIGN)
            constant[i+1-skipped] = constant[i-skipped] / constant[i+1-skipped];
          skipped++;
          i += 2;
        }

        new_constant = realloc(new_constant, (i-skipped)*sizeof(float));
        printf("yes\n");
        new_constant[i-1-skipped] = constant[i-skipped];
      }

    }
    new_constant = realloc(new_constant, (i+1-skipped)*sizeof(float));
    new_constant[i-skipped] = constant[i-skipped];
    new_constant_size++;


    //print new constant and operater
    for(int i = 0; i < new_constant_size; i++){
     printf("new_number_: %f\n", new_constant[i]);
    }
    for(int i = 0; i < new_operater_size; i++){
     printf("new_operator_: %d\n", new_operater[i]);
    }

   //calculate new expression
    short k = 0;
    while(k < new_operater_size){

      if(new_operater[k] == PLUS_SIGN)
        new_constant[k+1] = new_constant[k] + new_constant[k+1];
      if(new_operater[k] == MINUS_SIGN)
        new_constant[k+1] = new_constant[k] - new_constant[k+1];

      k++;
    }
    result = new_constant[k];
    free(new_constant);
    free(new_operater);

  }else if(operator_size == constant_size - 1 ){
    //calculate  expression
     short k = 0;
     while(k < operator_size){

       if(operator[k] == MULTIPLY_SIGN)
         constant[k+1] = constant[k] * constant[k+1];
       if(operator[k] == DIVIDE_SIGN)
         constant[k+1] = constant[k] / constant[k+1];

       k++;
     }
     result = constant[k];
  }


  return result;
}
