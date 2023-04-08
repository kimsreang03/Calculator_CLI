#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/scanner.h"

Element* init_element(char* value, char type){

  Element* element = calloc(1, sizeof(struct ELEMENTS));
  element->value = value;
  element->type = type;

  return element;
}

Scanner* init_scanner(char* input){
  Scanner* scanner = calloc(1, sizeof(struct SCANNER));
  scanner->input = input;
  scanner->input_size = strlen(input);
  scanner->index = 0;
  scanner->current = input[scanner->index];
}

void scanner_advance(Scanner* scanner){
  if(scanner->index < scanner->input_size && scanner->current != '\0'){
    scanner->index++;
    scanner->current = scanner->input[scanner->index];
  }
}

Element* scanner_advance_current(Scanner* scanner, int type){
    char* value = calloc(2, sizeof(char));
    value[0] = scanner->current;
    value[1] = '\0';
    scanner_advance(scanner);
    return init_element(value, type);
}

void scanner_skip_whitespace(Scanner* scanner){
  while(scanner->current == 13 || scanner->current == 10 || scanner->current == ' ' || scanner->current == '\t'){
    scanner_advance(scanner);
  }
}// skip whitespace: ' ' \n '\t'

Element* scanner_constant(Scanner* scanner){
  char* value = calloc(1, sizeof(char)); // allocates for value
  while(isdigit(scanner->current) || scanner->current == '.'){
    value = realloc(value, (strlen(value) + 2)*sizeof(char)); // allocates more memory for value
    strcat(value, (char[]){scanner->current, 0});
    scanner_advance(scanner);
  }
  return init_element(value, CONSTANT); // return constant as string type
} //scan for constant

Element* scanner_next_element(Scanner* scanner){

  while(scanner->current != '\0'){
    scanner_skip_whitespace(scanner);
    if(isdigit(scanner->current)) return scanner_constant(scanner);

    //return type of each element
    switch(scanner->current){
      case '+': return scanner_advance_current(scanner, PLUS_SIGN);
      case '-': return scanner_advance_current(scanner, MINUS_SIGN);
      case '*': return scanner_advance_current(scanner, MULTIPLY_SIGN);
      case '/': return scanner_advance_current(scanner, DIVIDE_SIGN);
      case '=': return scanner_advance_current(scanner, EQUAL_SIGN);
      case '(': return scanner_advance_current(scanner, LEFT_PARENTHESIS);
      case ')': return scanner_advance_current(scanner, RIGHT_PARENTHESIS);
      case '[': return scanner_advance_current(scanner, LEFT_BRACKET);
      case ']': return scanner_advance_current(scanner, RIGHT_BRACKET);
      case '{': return scanner_advance_current(scanner, LEFT_BRACE);
      case '}': return scanner_advance_current(scanner, RIGHT_BRACE);
      case '<': return scanner_advance_current(scanner, LESSTHAN_SIGN);
      case '>': return scanner_advance_current(scanner, GREATERTHAN_SIGN);
      case '^': return scanner_advance_current(scanner, CARET);
      case '!': return scanner_advance_current(scanner, EXCLAMATION);
      case '%': return scanner_advance_current(scanner, PERCENT_SIGN);

      default: printf("[scanner]: unexpected character %s\n", scanner->current);
      exit(1); break;
    }
  }

  return init_element(0, EOI); //END OF FILE
}
