#include "board.h"
#include <iostream>

int main(){
  Board game1;
  int row, column;
  game1.displayRules(std::cout);
  game1.display(std::cout);
  while(getPhase() == 1){
    game1.getMove1(1, std::cout);
    game1.getMove1(2, std::cout);}
  
  return 0;
}


