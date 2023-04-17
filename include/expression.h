#ifndef CAL_EXPRESSION_H
#define CAL_EXPRESSION_H

extern short input_size;

void push(char* stack, char element);
char pop(char* stack);
int precedence(char symbol);
int isOperator(char symbol);
char* convert_infix_to_postfix(char* infix);
void push_int(int* stack_int, int element);
char pop_int(int* stack_int);
int evaluate_postfix(char *postfix);


#endif
