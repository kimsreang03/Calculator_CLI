
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/expression.h"


// Function to return precedence of operators
int precedence(char operator)
{
	switch (operator) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}

// Function to check if the scanned character
// is an operator
int isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/'
			|| ch == '^');
}

// Main functio to convert infix expression
// to postfix expression
char* infixToPostfix(char* infix)
{

  char space = ' ';

	int i, j;
	int len_infix = strlen(infix);
	char* postfix = calloc(2*len_infix, sizeof(char));

	char stack[len_infix];
	int top = -1;

	for (i = 0, j = 0; i < len_infix; i++) {
		// if (infix[i] == ' ' || infix[i] == '\t')
		// 	continue;

		// If the scanned character is operand
		// add it to the postfix expression
		if (isalnum(infix[i])) {
			postfix[j++] = infix[i];
			if(isOperator(infix[i+1])) postfix[j++] = space;
			if(infix[i+1] == ')') postfix[j++] = space;
			else if(i == len_infix - 1) postfix[j++] = space;
		}

		// if the scanned character is '('
		// push it in the stack
		else if (infix[i] == '(') {
			stack[++top] = infix[i];
		}

		// if the scanned character is ')'
		// pop the stack and add it to the
		// output string until empty or '(' found
		else if (infix[i] == ')') {
			while (top > -1 && stack[top] != '('){
				postfix[j++] = stack[top--];
        postfix[j++] = space;
			}
			if (top > -1 && stack[top] != '(')
				return "Invalid Expression";
			else
				top--;
		}

		// If the scanned character is an operator
		// push it in the stack
		else if (isOperator(infix[i])) {
			while (top > -1
				&& precedence(stack[top])
						>= precedence(infix[i])){
				postfix[j++] = stack[top--];
        postfix[j++] = space;
			}
			stack[++top] = infix[i];
		}
	}

	// Pop all remaining elements from the stack
	while (top > -1) {
		if (stack[top] == '(') {
			return "Invalid Expression";
		}
		postfix[j++] = stack[top--];
	}
	postfix[j] = '\0';
	return postfix;
}

int evaluate_postfix(char *postfix){

	short postfix_len = strlen(postfix);

	int stack[postfix_len];
	short top = -1;

	short i;
	for(i = 0; postfix[i]; i++){
		if(postfix[i] == ' ') continue;

		else if(isdigit(postfix[i])){
			int num = 0;
			while(isdigit(postfix[i])){
				num = num*10 + (postfix[i] - '0');
				i++;
			}
			i--;
			stack[++top] = num;
		}
		else{
			int operand_2 = stack[top--];
			int operand_1 = stack[top--];

			switch(postfix[i]){
				case '+': stack[++top] = operand_1 + operand_2; break;
				case '-': stack[++top] = operand_1 - operand_2; break;
				case '*': stack[++top] = operand_1 * operand_2; break;
				case '/': stack[++top] = operand_1 / operand_2; break;

			}

		}

	}
	return stack[top--];
}
