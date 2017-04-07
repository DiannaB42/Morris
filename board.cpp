#include "board.h"

Board::Board(){
  //constructo for board. Assigns all places 'e' signiying empty, and sets phase to 1
  //and sets move counters to 0.
  phase = 1;
  playCounter1 = 0;
  playCounter2 = 0;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 8; j++){
      game[i][j]='e'; } } }

int Board::countPieces(int player){
  //Counts the number of pieces played by the player. If invalid player id entered,
  //it counts the number of blank spaces.
  int count = 0;
  char c = 'e';
  if(player == 1)
    c = '@';
  else if (player == 2)
    c = 'X';
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 8; j++){
      if(game[i][j]== c)
	count++; } }
  return count; }


int Board::checkMills(int player, int row, int column){
  //checks for mills created by move in row, column for player. Should have row and column
  //already converted to index of the array game row between 0 and 2 column between 0 and 7
  char c = getPlayerSymbol(player);
  int counter = 0;
  if( c != 'b'){ //ensures an actual player number is entered
    if(row == 0){
      if(column == 0 || column ==1 || column == 2){
	if(getPiece(0,0) == c && getPiece(0,1) == c && getPiece(0,2) == c)
	  counter++;} 
      if(column == 0 || column == 3 || column == 5){
	if(getPiece(0,0) == c && getPiece(0,3) == c && getPiece(0,5) == c)
	  counter++;}
      if(column == 2 || column == 4 || column == 7){
	if(getPiece(0,2) == c && getPiece(0,4) == c && getPiece(0,7) == c)
	  counter++;}
      if(column == 5 || column == 6 || column == 7){
	if(getPiece(0,5) == c && getPiece(0,6) == c && getPiece(0,7) == c)
	  counter++;} }
    else if(row == 1){
      if(column == 0 || column == 1 || column ==2){
	if(getPiece(1,0) == c && getPiece(1,1) == c && getPiece(1,2) == c)
	  counter++;} 
      if(column == 0 || column == 3 || column == 5){
	if(getPiece(1,0) == c && getPiece(1,3) == c && getPiece(1,5) == c)
	  counter++;}
      if(column == 2 || column == 4 || column == 7){
	if(getPiece(1,2) == c && getPiece(1,4) == c && getPiece(1,7) == c)
	  counter++;}
      if(column == 5 || column == 6 || column == 7){
	if(getPiece(1,5) == c && getPiece(1,6) == c && getPiece(1,7) == c)
	  counter++;} }
    else if(row == 2){
      if(column == 0 || column == 1 || column == 2){
	if(getPiece(2,0) == c && getPiece(2,1) == c && getPiece(2,2) == c)
	  counter++;} 
      if(column == 0 || column == 3 || column == 5){
	if(getPiece(2,0) == c && getPiece(2,3) == c && getPiece(2,5) == c)
	  counter++;}
      if(column == 2 || column == 4 || column == 7){
	if(getPiece(2,2) == c && getPiece(2,4) == c && getPiece(2,7) == c)
	  counter++;}
      if(column == 5 || column == 6 || column == 7){
	if(getPiece(2,5) == c && getPiece(2,6) == c && getPiece(2,7) == c)
	  counter++;} }
    if( column == 1){
      if(getPiece(0,1) == c && getPiece(1,1) == c && getPiece(2,1) == c)
	  counter++;}
    if( column == 3){
      if(getPiece(0,3) == c && getPiece(1,3) == c && getPiece(2,3) == c)
	  counter++;}
    if( column == 4){
      if(getPiece(0,4) == c && getPiece(1,4) == c && getPiece(2,4) == c)
	  counter++;}
    if( column == 6){
      if(getPiece(0,6) == c && getPiece(1,6) == c && getPiece(2,6) == c)
	  counter++;}
    return counter;} 
  return 0;}

char Board::getPlayerSymbol(int player){
  if(player == 1)
    return '@';
  else if (player == 2)
    return 'X';
  return 'b';}

bool Board::removePiece(int row, int column){
  if(game[row][column]== 'e')
    return false;
  else{
    game[row][column]= 'e';
    return true;} }

std::ostream& Board::getMove1(int player, std::ostream& output){
  int row = 0, column = 0, mills = 0;
  char c;
  display(output);
  output << "Player " << player << " turn. Please place a piece.\n";
  if(getPhase() == 1){
    output << "You can place a new piece anywhere that is free.\n";
    output << "Please pick the row of the point (1-7).\n";
    std::cin >> row; 
    output << "Please pick the column of the point (1-7).\n";
    std::cin >> column;
    int error = checkValues(row, column);
    errorMessage(error, output);
    while(error !=0){
      output << "Please pick the row of the point (1-7).\n";
      std::cin >> row; 
      output << "Please pick the column of the point (1-7).\n";
      std::cin >> column;
      error = checkValues(row, column);
      errorMessage(error, output);}
    play(player, row, column);
    spotConverter(row, column);
    mills = checkMills(player, row, column);
    if(mills != 0){
      output << "Player " << player << " has made a mill. You can remove an opponent's piece.\n"
	     << "Enter the row of the piece you want to remove.\n";
      std::cin >> row;
      output << "Enter the column of the piece you want to remove.\n";
      std::cin >> column;
      error = checkValuesMills(player, row, column);
      errorMessageMills(error, output);
      while(error != 0){
	output << "Player " << player << " has made a mill. You can remove an opponent's piece.\n"
	       << "Enter the row of the piece you want to remove.\n";
	std::cin >> row;
	output << "Enter the column of the piece you want to remove.\n";
	std::cin >> column;
	error = checkValuesMills(player, row, column);
	errorMessageMills(error, output);}
      spotConverter(row, column);
      removePiece(row, column);}
    return output;} }

std::ostream& Board::getMove2(int player, std::ostream& output){
  int row = 0, column = 0, mills = 0, error, opponent;
  char move;
  display(output);
  if(player == 1)
    opponent = 2;
  else if(player ==2)
    opponent = 1;
  else
    return output;
  if(getPhase() == 2){
    output << "Player " << player << " turn. Please select a piece to move.\n";
    output << "Select the row of the piece you want to move.\n";
    std::cin >> row;
    output << "Select the column of the piece you want to move.\n";
    std::cin >> column;
    error = checkValuesMills(opponent, row, column);
    output << errorMessageMills(error);
    while(error !=0){
      output << "Select the row of the piece you want to move.\n";
      std::cin >> row;
      output << "Select the column of the piece you want to move.\n";
      std::cin >> column;
      error = checkValuesMills(opponent, row, column);
      output << errorMessageMills(error);}
    output << "Select the direction of the move - u for up, d for down, l for left, r for right\n";
    std::cin >> move;
  }

}

std::ostream& Board::errorMessage(int error, std::ostream& output){
  if(error == 1)
    output << "Row number not in range 1-7\n";
  else if(error == 2)
    output << "Column number not in range 1-7\n";
  else if(error == 3)
    output << "Spot not on the board.\n";
  else if (error == 4)
    output << "Spot already taken.\n";}


std::ostream& Board::errorMessageMills(int error, std::ostream& output){
  if(error == 1)
    output << "Row number not in range 1-7\n";
  else if (error == 2)
    output << "Column number not in range 1-7\n";
  else if (error == 3)
    output << "Spot not on the board.\n";
  else if (error == 4)
    output << "No piece in that spot.\n";
  else if (error == 5)
    output << "Not your opponent's piece.\n"; }

int Board::checkValues(int row, int column){
  //checks that row and column location correspond to a spot that can be played
  //needs to be on the board and free. Returns an error code if the location is
  //not playable
  if( row <=0 || row > 7)
    return 1;
  else if(column <=0 || column > 7)
    return 2;
  if(checkValid(row,column)== false)
    return 3;
  spotConverter(row, column);
  if(checkEmpty(row, column) == false)
    return 4;
  return 0; }

 int Board::checkValuesMills(int player, int row, int column){
   char c = getPlayerSymbol(player);
   if( row <=0 || row > 7)
    return 1;
  else if(column <=0 || column > 7)
    return 2;
  if(checkValid(row,column)== false)
    return 3;
  spotConverter(row, column);
  if(checkEmpty(row, column) == true)
    return 4;
  if( c == getPiece(row,column))
    return 5;
  return 0;}



bool Board::checkValid(int row, int column){
  //checks that the specific spot is actually on the board, as the row and columns
  //have empty spaces in them. Returns true if it is, false if not
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
  return false; }

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
      return;}}}

std::ostream& Board::displayRules(std::ostream& output){
  if(phase == 1){
    output<< "PHASE 1\n"
	  << "Players put down 9 pieces on the board in free spaces\n"
	  << "(spaces marked by 0). If any player makes a row of three\n"
	  << "of their pieces, they can remove a piece from the opponent.";} }

bool Board::playLocation(int player, int row, int column){
  //assigns value to spot played. Helper function for use inside play. Advances move counters
  //playCounter1 and playCounter2
  if(game[row][column] == 'e'){
    if(player == 1){
      game[row][column]= '@';
      playCounter1++;}
    else{
      game[row][column]='X';
      playCounter2++;} 
    if(playCounter1 == getMaxPieces() && playCounter2 == getMaxPieces())
      advancePhase();}
  else
    return false; }

bool Board::play(int player, int row, int column){
  //attempts to play location
  if(player != 1 && player != 2)
    return false;
  else{
    spotConverter(row, column);
    if(row != -1)
      if(checkEmpty(row, column))
	 playLocation(player, row,column);} }



std::ostream& Board::display(std::ostream& output){
  output << "\n   1  2  3        4        5  6  7\n\n";
  //Printing Row 1, game[0][0] to game[0][2]
  output << "1  ";
  printPiece(0,0,output);
  output  << "--------------";
  printPiece(0,1,output);
  output  << "--------------";
  printPiece(0,2,output);
  output << "\n                  |\n";
  //Printing Row2
  output << "2  |  ";
  printPiece(1,0,output);
  output  << "-----------";
  printPiece(1,1,output);
  output  << "-----------";
  printPiece(1,2,output);
  output << "  |  ";
  output << "\n                  |\n";
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
  output << "\n                  |\n";
  //Printing Row 6
  output << "6  |  ";
  printPiece(1,5,output);
  output  << "-----------";
  printPiece(1,6,output);
  output  << "-----------";
  printPiece(1,7,output);
  output << "  |";
  output << "\n                  |\n";
  //Printing Row 7
  output << "7  ";
  printPiece(0,5,output);
  output  << "--------------";
  printPiece(0,6,output);
  output  << "--------------";
  printPiece(0,7,output);
  output << "\n\n";
  return output;}


std::ostream& Board::printPiece(int row, int column, std::ostream& output){
  if(checkEmpty(row, column)== true)
    output << "O";
  else
    output << game[row][column];
  return output;}
