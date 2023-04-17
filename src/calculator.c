#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/scanner.h"
#include "../include/calculator.h"
#include "../include/callib.h"
#include "../include/expression.h"

void calculator(char* input){

  char* postfix = convert_infix_to_postfix(input);
  int result = evaluate_postfix(postfix);

  printf("the result is %d\n", result);

}
