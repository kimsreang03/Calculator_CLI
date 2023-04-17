#include "../include/expression.h"
#include "../include/scanner.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

short test = 5;
short top = -1;

void push(char* stack, char element) {
   stack[++top]=element;
}
char pop(char* stack) {
   return stack[top--];
}

//returns precedence of operators
int precedence(char symbol) {
   switch(symbol) {
      case '+':
      case '-':
         return 2;
         break;
      case '*':
      case '/':
         return 3;
         break;
      case '^':
         return 4;
         break;
      case '(':
      case ')':
      case '#':
         return 1;
         break;
   }
}

//check whether the symbol is operator?
int isOperator(char symbol) {
   switch(symbol){
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '(':
      case ')':
         return 1;
      break;
         default:
         return 0;
   }
}

char* convert_infix_to_postfix(char* infix){
  char* stack = calloc(test + 1, sizeof(char));

  char* postfix = calloc(1, sizeof(char));
  short postfix_size = 0;
  short infix_size = strlen(infix);
  short i, symbol;
  stack[++top] = '#';
  for(i = 0; i < infix_size; i++){
    symbol = infix[i];
    if(isOperator(symbol) == 0){
      postfix = realloc(postfix, (postfix_size + 2) * sizeof(char));
      postfix[postfix_size] = symbol;
      postfix_size++;
    }else{
      if(symbol == '(') push(stack,symbol);
      else{
        if(symbol == ')'){
          while(stack[top]!='('){
            postfix = realloc(postfix, (postfix_size + 2) * sizeof(char));
             postfix[postfix_size] = pop(stack);
             postfix_size++;
          }
          pop(stack);//pop out (.
        }else{
          if(precedence(symbol)>precedence(stack[top])) push(stack, symbol);
             else {
             while(precedence(symbol)<=precedence(stack[top])) {
               postfix = realloc(postfix, (postfix_size + 2) * sizeof(char));
                postfix[postfix_size] = pop(stack);
                postfix_size++;
             }
             push(stack, symbol);
          }
        }
      }
    }
  }
  while(stack[top] != '#') {
     postfix[postfix_size] = pop(stack);
     postfix_size++;
  }
  postfix[postfix_size] = '\0';

  free(stack);
  return postfix;
}

short top_int = -1;

void push_int(int* stack_int, int element) {
   stack_int[++top_int] = element;
}

char pop_int(int* stack_int) {
   return stack_int[top_int--];
}

int evaluate_postfix(char *postfix){
  int* stack_int = calloc(input_size + 1,sizeof(int));
  char ch;
  int i=0,operand1,operand2;

  while( (ch=postfix[i++]) != '\0') {
    if(isdigit(ch)) push_int(stack_int, ch-'0'); // Push the operand
    else {
      //Operator,pop two  operands
      operand2 = pop_int(stack_int);
      operand1 = pop_int(stack_int);
      switch(ch) {
        case '+': push_int(stack_int, operand1+operand2); break;
        case '-': push_int(stack_int, operand1-operand2); break;
        case '*': push_int(stack_int, operand1*operand2); break;
        case '/': push_int(stack_int, operand1/operand2); break;
      }
    }
  }
  free(postfix);
  int result = stack_int[top_int];
  free(stack_int);
  return result;
}
