#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/scanner.h"

short input_size = 0;

char* getinput(){

  char* input = calloc(101, sizeof(char));
  printf("input => " );
  scanf("%100[^\n]s", input);

  input = delete_whitespace(input);
  return input;
}

char* delete_whitespace(char* input){
  char* new_input = calloc(1, sizeof(char));
  short i = 0;

  while(input[i] != 0){
    if(input[i] != ' '){
      new_input = realloc(new_input, (input_size + 2) * sizeof(char) );
      new_input[input_size] = input[i];
      input_size++;
    }
    i++;
  }
  new_input[input_size] = '\0';
  free(input);
  return new_input;
}
