#include "board.h"
#include <iostream>

int main(){
  Board game1;
  int row, column;
  game1.displayRules(std::cout);
  game1.display(std::cout);
  game1.play(std::cout);  
  return 0;
}


