#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/scanner.h"
#include "../include/calculator.h"
#include "../include/expression.h"

void calculator(char* input){

  char* postfix = infixToPostfix(input);
  int result = evaluate_postfix(postfix);
	// printf("postfix: %s\n", postfix);
	free(postfix);
  printf("the result is %d\n", result);
}
