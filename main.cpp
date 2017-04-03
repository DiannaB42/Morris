#include "board.h"
#include <iostream>

int main(){
  Board game1;
  int row, column;
  game1.display(std::cout);
  //for(int i=0; i <9;i++){
  game1.getMove(1, std::cout);
    //}
  game1.display(std::cout);
  return 0;
}


