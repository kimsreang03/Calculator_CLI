#ifndef CAL_EXPRESSION_H
#define CAL_EXPRESSION_H

extern short input_size;


int precedence(char operator);
int isOperator(char ch);
char* infixToPostfix(char* infix);
int evaluate_postfix(char *postfix);


#endif
