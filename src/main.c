#include <stdio.h>
#include <stdlib.h>
#include "../include/calculator.h"

int main(int argc, char **argv){

  //get input from user
  char* input = calloc(101, sizeof(char));
  if(input == NULL) return 1;
  printf("\ninput => ");
  scanf("%100[^\n]s", input);


  calculator(input);

  free(input);
  return 0;
}
