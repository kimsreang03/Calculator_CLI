#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/scanner.h"

char* getinput(){

  char* input = calloc(101, sizeof(char));
  printf("input => " );
  scanf("%100[^\n]s", input);

  input = delete_whitespace(input);

  return input;
}

char* delete_whitespace(char* input){
  char* new_input = calloc(1, sizeof(char));
  short i = 0, size = 0;
  while(input[i] != 0){
    if(input[i] != ' '){
      new_input = realloc(new_input, (size + 2) * sizeof(char) );
      new_input[size] = input[i];
      size++;
    }
    i++;
  }
  new_input[size] = '\0';
  
  return new_input;
}
