#ifndef CAL_SCANNER_H
#define CAL_SCANNER_H

#include <stdio.h>

typedef struct SCANNER{

  char* input;
  size_t input_size;
  char current;
  unsigned int index;

}Scanner;

typedef struct ELEMENTS{

  char* value;
  enum{
    CONSTANT, // 0: number
    PLUS_SIGN, // 1: +
    MINUS_SIGN, // 2: -
    MULTIPLY_SIGN, // 3: *
    DIVIDE_SIGN, // 4: /
    EQUAL_SIGN, // 5: =
    LEFT_PARENTHESIS, // 6: (
    RIGHT_PARENTHESIS, // 7: )
    LEFT_BRACKET, // 8: [
    RIGHT_BRACKET,// 9: ]
    LEFT_BRACE, // 10: {
    RIGHT_BRACE, // 11: }
    LESSTHAN_SIGN, // 12: <
    GREATERTHAN_SIGN, // 13: >
    CARET, // 14: ^
    EXCLAMATION, // 15: !
    PERCENT_SIGN, // 16: %
    EOI, // 17: END OF INPUT
  }type;

}Element;

Element* init_element(char* value, char type);

Scanner* init_scanner(char* input);

void scanner_advance(Scanner* scanner);

Element* scanner_advance_current(Scanner* scanner, int type);

void scanner_skip_whitespace(Scanner* scanner);

Element* scanner_constant(Scanner* scanner);

Element* scanner_next_element(Scanner* scanner);

#endif
