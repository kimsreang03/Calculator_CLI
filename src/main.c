#include <stdio.h>
#include <stdlib.h>
#include "../include/scanner.h"
#include "../include/calculator.h"


int main(int argc, char **argv){

  //get input from user
  char* input = getinput();

  calculator(input);

  free(input);
  return 0;
}
