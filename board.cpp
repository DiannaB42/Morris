#include "board.h"

Board::Board(){
  phase=1;
  for (int i =0; i < 3; i++){
    for (int j=0; j < 8; j++){
      game[i][j]='e';
    }
  }
}


std::ostream& Board::getMove(int player, std::ostream& output){
  int row = 0, column = 0;
  displayRules(output);
  display(output);
  output << "Player " << player << " turn. Please place a piece.\n";
  if(getPhase() == 1){
    output << "You can place a new piece anywhere that is free.\n";
    output << "Please pick the row of the point (1-7).\n";
    std::cin >> row; 
    output << "Please pick the column of the point (1-7).\n";
    std::cin >> column;
    int error = checkValues(row, column);
    if(error == 1)
      output << "Row number not in range 1-7\n";
    else if(error == 2)
      output << "Column number not in range 1-7\n";
    else if(error == 3)
      output << "Spot " << row << ", " << column << " not on the board.\n";
    else if (error == 4)
      output << "Spot " << row << ", " << column << " already taken.\n";
    while(error !=0){
      output << "Please pick the row of the point (1-7).\n";
      std::cin >> row; 
      output << "Please pick the column of the point (1-7).\n";
      std::cin >> column;
      error = checkValues(row, column);
      if(error == 1)
	output << "Row number not in range 1-7\n";
      else if(error == 2)
	output << "Column number not in range 1-7\n";
      else if(error == 3)
	output << "Spot " << row << ", " << column << " not on the board.\n";
      else if (error == 4)
	output << "Spot " << row << ", " << column << " already taken.\n";
    }
    play(player, row, column);
    display(output);
  }
  output << "\n\n";
  return output;
}

int Board::checkValues(int row, int column){
  if( row == 0 )
    return 1;
  else if(column <=0 || column > 7)
    return 2;
  if(checkValid(row,column)== false)
    return 3;
  spotConverter(row, column);
  if(checkEmpty(row, column) == false)
    return 4;
  return 0;
  }



bool Board::checkValid(int row, int column){
  if(row == 1 || row == 7){
    if(column == 1 || column == 4 || column == 7)
      return true;
    else
      return false;}
  if(row == 2 || row == 6){
    if(column == 2 || column == 4 || column == 6)
      return true;
    else
      return false;}
  if(row == 3 || row == 5){
    if(column == 3 || column == 4 || column == 5)
      return true;
    else
      return false;}
  if(row == 4){
    if(column == 1 || column == 2 ||column == 3 || column == 5 || column == 6 ||column == 7)
      return true;
    else
      return false;}
  return false;
}

void Board::spotConverter(int& row, int& column){
  //Given the row 1-7 and column 1-7 gives the internal storage location for that spot 0-2, 0-7
  if(row == 1){
    if (column ==1){
      row = 0;
      column = 0;}
    else if(column ==4){
      row = 0;
      column = 1;}
    else if(column ==7){
      row = 0;
      column = 2;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 2){
    if (column == 2){
      row = 1;
      column = 0;}
    else if(column == 4){
      row = 1;
      column = 1;}
    else if(column == 6){
      row = 1;
      column = 2;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 3){
    if (column == 3){
      row = 2;
      column = 0;}
    else if(column == 4){
      row = 2;
      column = 1;}
    else if(column == 5){
      row = 2;
      column = 2;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 4){
    if (column ==1){
      row = 0;
      column = 3;}
    else if(column ==2){
      row = 1;
      column = 3;}
    else if(column ==3){
      row = 2;
      column = 3;}
    else if(column == 5){
      row = 2;
      column = 4;}
    else if(column == 6){
      row = 1;
      column = 4;}
    else if(column == 7){
      row = 0;
      column = 4;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 5){
    if (column == 3){
      row = 2;
      column = 5;}
    else if(column == 4){
      row = 2;
      column = 6;}
    else if(column == 5){
      row = 2;
      column = 7;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 6){
    if (column ==2){
      row = 1;
      column = 5;}
    else if(column ==4){
      row = 1;
      column = 6;}
    else if(column ==6){
      row = 1;
      column = 7;}
    else{
      row = -1;
      column = -1;
      return;}}
 if(row == 7){
    if (column == 1){
      row = 0;
      column = 5;}
    else if(column == 4){
      row = 0;
      column = 6;}
    else if(column ==7){
      row = 0;
      column = 7;}
    else{
      row = -1;
      column = -1;
      return;}}
}


std::ostream& Board::displayRules(std::ostream& output){
  output<< "PHASE 1\n"
	<< "Players put down 9 pieces on the board in free spaces\n"
	<< "(spaces marked by 0). If any player makes a row of three\n"
	<< "of their pieces, they can remove a piece from the opponent.";
}

bool Board::playLocation(int player, int row, int column){
  if(game[row][column] == 'e'){
    if(player == 1){
      game[row][column]= '@';
    }
    else{
      game[row][column]='X';
    }
  }
  else
    return false;
}

bool Board::play(int player, int row, int column){
  if(player != 1 && player != 2)
    return false;
  else{
    spotConverter(row, column);
    if(row != -1)
      playLocation(player, row,column);
  }
}



std::ostream& Board::display(std::ostream& output){
  output << "\n   1  2  3        4        5  6  7\n\n";
  //Printing Row 1, game[0][0] to game[0][2]
  output << "1  ";
  printPiece(0,0,output);
  output  << "--------------";
  printPiece(0,1,output);
  output  << "--------------";
  printPiece(0,2,output);
  output << "\n\n";
  //Printing Row2
  output << "2  |  ";
  printPiece(1,0,output);
  output  << "-----------";
  printPiece(1,1,output);
  output  << "-----------";
  printPiece(1,2,output);
 output << "  |  ";
  output << "\n\n";
  //Printing Row 3
  output << "3  |  |  ";
  printPiece(2,0,output);
  output  << "--------";
  printPiece(2,1,output);
  output  << "--------";
  printPiece(2,2,output);
  output << "  |  |  ";
  output << "\n\n   |  |  |                 |  |  |\n\n";
  //Printing Row 4
 output << "4  ";
  printPiece(0,3,output);
  output  << "--";
  printPiece(1,3,output);
  output  << "--";
  printPiece(2,3,output);
 output << "                 ";
  printPiece(2,4,output);
  output  << "--";
  printPiece(1,4,output);
  output  << "--";
  printPiece(0,4,output); 
  output << "\n\n   |  |  |                 |  |  |\n\n";
  //Printing Row 5
  output << "5  |  |  ";
  printPiece(2,5,output);
  output  << "--------";
  printPiece(2,6,output);
  output  << "--------";
  printPiece(2,7,output);
 output << "  |  |  ";
  output << "\n\n";
  //Printing Row 6
  output << "6  |  ";
  printPiece(1,5,output);
  output  << "-----------";
  printPiece(1,6,output);
  output  << "-----------";
  printPiece(1,7,output);
  output << "  |\n\n";
  //Printing Row 7
  output << "7  ";
  printPiece(0,5,output);
  output  << "--------------";
  printPiece(0,6,output);
  output  << "--------------";
  printPiece(0,7,output);
  output << "\n\n";
  return output;
}


std::ostream& Board::printPiece(int row, int column, std::ostream& output){
  if(checkEmpty(row, column)== true)
    output << "O";
  else
    output << game[row][column];
  return output;
}
