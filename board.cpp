#include "board.h"

Board::Board(){
<
  //constructor for board. Assigns all places 'e' signiying empty, and sets phase to 1
  //and sets move counters to 0.
  phase = 1;
  playCounter1 = 0;
  playCounter2 = 0;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 8; j++){
      game[i][j]='e'; } } }

std::ostream& Board::play(std::ostream& output){
  if(countPieces(1) != 0 || countPieces(2) != 0)
    return output;
  else{
    for(int i = 0 ; i < getMaxPieces(); i++){
      move1(1, output);
      move1(2, output);}
    advancePhase();
    int player = 0;
    while(getPhase() == 2){
      move2((player % 2)+1, output);
      player++;}
    while(getPhase() == 3){
      move3((player % 2)+1, output);
      player++;}
    player--;
    output << "Player " << player % 2 +1 <<  " won with " << countPieces((player % 2)+1)
	   << " left on the board.";
      return output;}}



int Board::countPieces(int player){
  //Counts the number of pieces played by the player. If invalid player id entered,
  //it counts the number of blank spaces.
  int count = 0;
  char c = 'e';
  if(player == 1)
    c = getPlayerSymbol(1);
  else if (player == 2)
    c = getPlayerSymbol(2);
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
  //specifies the character associated with each player
  if(player == 1)
    return '@';
  else if (player == 2)
    return 'X';
  return 'b';}


std::ostream& Board::move1(int player, std::ostream& output){
  // controls movement in the first part of the game
  int row = 0, column = 0, mills = 0, opponent;
  char c;
  if(player == 1)
    opponent = 2;
  else if(player == 2)
    opponent = 1;
  display(output);
  output << "Player " << player << " turn. Please place a piece.\n";
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
  spotConverter(row, column);
  playLocation(player, row, column);
  mills = checkMills(player, row, column);
  while(mills > 0){
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
    removeLocation(opponent, row, column);
    mills--;}
  return output; }


std::ostream& Board::move2(int player, std::ostream& output){
  // controls movement in the second phase of the game
  int row = 0, column = 0, mills = 0, error, errorMove, opponent;
  int row1 = 0, column1 = 0;
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
    std::cin >> row1;
    output << "Select the column of the piece you want to move.\n";
    std::cin >> column1;
    error = checkValuesMills(opponent, row1, column1);
    errorMessage2(error,output);
    while(error != 0){
      output << "Select the row of the piece you want to move.\n";
      std::cin >> row1;
      output << "Select the column of the piece you want to move.\n";
      std::cin >> column1;
      error = checkValuesMills(opponent, row1, column1);
      errorMessage2(error,output);
      if(checkMoves(row1, column1)== false){
	output << "No possible moves for this piece. Choose a new piece.\n";
	error = 6;} }
    row = row1;
    column = column1;
    output << "Select the direction of the move - u for up, d for down, l for left, r for right\n";
    std::cin >> move; 
    errorMove = movePiece(player, row, column, move);
    while(errorMove != 1){
      row= row1;
      column = column1;
      output << "Select the direction of the move - u for up, d for down, l for left, r for right\n";
      std::cin >> move; 
      errorMove = movePiece(player, row, column, move);}
    mills = checkMills(player, row, column);
    while(mills > 0){
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
      removeLocation(opponent, row, column);
      mills--;
      if(playCounter1 <= 3 || playCounter2 <= 3)
	advancePhase();}
  } }


std::ostream& Board::move3(int player, std::ostream& output){
  // controls movement in the final phase of the game
  int row = 0, row1 = 0, column = 0, column1 = 0, mills = 0, error, errorMove, opponent;
  char move;
  display(output);
  if(player == 1)
    opponent = 2;
  else if(player ==2)
    opponent = 1;
  else
    return output;
  output << "Player " << player << " turn. Please select a piece to move.\n";
  output << "Select the row of the piece you want to move.\n";
  std::cin >> row;
  output << "Select the column of the piece you want to move.\n";
  std::cin >> column;
  error = checkValuesMills(opponent, row, column);
  errorMessage2(error,output);
  while(error != 0){
    output << "Select the row of the piece you want to move.\n";
    std::cin >> row;
    output << "Select the column of the piece you want to move.\n";
    std::cin >> column;
    error = checkValuesMills(opponent, row, column);
    errorMessage2(error,output); }
  output << "Please pick the row of the spot you want to move it to (1-7).\n";
  std::cin >> row1; 
  output << "Please pick the column of the spot you want to move it to (1-7).\n";
  std::cin >> column1;
  errorMove = checkValues(row1, column1);
  errorMessage(errorMove, output);
  while(errorMove !=0){
    output << "Please pick the row of the spot you want to move it to (1-7).\n";
    std::cin >> row1; 
    output << "Please pick the column of the spot you want to move it to (1-7).\n";
    std::cin >> column1;
    errorMove = checkValues(row1, column1);
    errorMessage(errorMove, output);}
  spotConverter(row, column);
  spotConverter(row1, column1);
  removeLocation(player, row, column);
  playLocation(player, row, column);
  mills = checkMills(player, row, column);
  while(mills > 0){
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
    removeLocation(opponent, row, column);
    mills--;}
  if(playCounter1 <= 0 || playCounter2 <= 0)
    advancePhase();
  return output;} 



bool Board::checkMoves(int row, int column){
  //Checks whether there are any free spaces in spots adjacent to the spot specified
  // uses player interface notation for location of spots
  spotConverter(row, column);
  if (column == 0){
    if(checkEmpty(row, 1) == true || checkEmpty(row, 3) == true)
      return true;
    else
      return false;}
  if (column == 2){
    if(checkEmpty(row, 1) == true || checkEmpty(row, 4) == true)
      return true;
    else return false;}
  if (column == 5){
    if(checkEmpty(row, 3) == true || checkEmpty(row, 6) == true)
      return true;
    else return false;}
  if (column == 7){
    if(checkEmpty(row, 6) == true || checkEmpty(row, 4) == true)
      return true;
    else return false;}  
  if (column == 1){
    if(checkEmpty(row, 0) == true || checkEmpty(row, 2) == true)
      return true;
    else if (row == 0){
      if(checkEmpty(row + 1, column) == true)
	return true;}
    else if (row == 1){
      if(checkEmpty(row + 1, column) == true || checkEmpty(row - 1, column) == true)
	return true;}
    else if (row == 2){
      if(checkEmpty(row -1, column) == true)
	return true;}
    else
      return false;}
 if (column == 6){
    if(checkEmpty(row, 5) == true || checkEmpty(row, 7) == true)
      return true;
    else if (row == 0){
      if(checkEmpty(row + 1, column) == true)
	return true;}
    else if (row == 1){
      if(checkEmpty(row + 1, column) == true || checkEmpty(row - 1, column) == true)
	return true;}
    else if (row == 2){
      if(checkEmpty(row - 1, column) == true)
	return true;}
    else
      return false;} 
 if (column == 3){
    if(checkEmpty(row, 0) == true || checkEmpty(row, 5) == true)
      return true;
    else if (row == 0){
      if(checkEmpty(row + 1, column) == true)
	return true;}
    else if (row == 1){
      if(checkEmpty(row + 1, column) == true || checkEmpty(row - 1, column) == true)
	return true;}
    else if (row == 2){
      if(checkEmpty(row - 1, column) == true)
	return true;}
    else
      return false;}
 if (column == 4){
    if(checkEmpty(row, 2) == true || checkEmpty(row, 7) == true)
      return true;
    else if (row == 0){
      if(checkEmpty(row + 1, column) == true)
	return true;}
    else if (row == 1){
      if(checkEmpty(row + 1, column) == true || checkEmpty(row - 1, column) == true)
	return true;}
    else if (row == 2){
      if(checkEmpty(row -1, column) == true)
	return true;}
    else
      return false;}
 return false;
}

int Board::movePiece(int player, int& row, int& column, char move){
  spotConverter(row, column);
  if (column == 0){
    if( move == 'd'){
      if(checkEmpty(row, 3) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 3);
	column = 3;
	return 1;}
      else
	return -1;}
    else if(move == 'r'){
      if(checkEmpty(row, 1) == true){
	removeLocation(player, row, column);
	playLocation(player,row,1);
	column = 1;
        return 1;}
      else
	return -1;}
    else
      return -1;}
  if (column == 2){
    if( move == 'd'){
      if(checkEmpty(row, 4) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 4);
	column = 4;
	return 1;}
      else
	return -1;}
    else if(move == 'l'){
      if(checkEmpty(row, 1) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 1);
	column = 1;
	return 1;}
      else
	return -1;}
    else
      return -1;}
  if (column == 5){
    if( move == 'u'){
      if(checkEmpty(row, 3) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 3);
	column = 3;
	return 1;}
      else
	return -1;}
    else if(move == 'r'){
      if(checkEmpty(row, 6) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 6);
	column = 6;
	return 1;}
      else
	return -1;}
    else
      return -1;}
  if (column == 7){
    if( move == 'u'){
      if(checkEmpty(row, 4) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 4);
	column = 4;
	return 1;}
      else
	return -1;}
    else if(move == 'l'){
      if(checkEmpty(row, 6) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 6);
	column = 6;
	return 1;}
      else
	return -1;}
    else
      return -1;}
  if(column == 1){
    if( move == 'l'){
      if(checkEmpty(row, 0) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 0);
	column = 0;
	return 1;}
      else
	return-1;}
    else if(move == 'r'){
      if(checkEmpty(row, 2) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 2);
	column =2;
	return 1;}
      else
	return -1;}
    if(row == 0 || row == 1){
      if(move == 'd'){
	if(checkEmpty(row+1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row+1, column);
	  row++;
          return 1;}
	else
	  return -1;}}
    if(row == 1 || row == 2){ 
      if(move == 'u'){
	if(checkEmpty(row-1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row-1, column);
	  row--;
	  return 1;}
	else
	  return -1;}}
    else
      return -1;}
  if(column == 6){
    if( move == 'l'){
      if(checkEmpty(row, 5) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 5);
	column = 5;
	return 1;}
      else
	return -1;}
    else if(move == 'r'){
      if(checkEmpty(row, 7) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 7);
	column = 7;
	return 1;}
      else
	return -1;}
    if(row == 0 || row == 1){
      if(move == 'u'){
	if(checkEmpty(row+1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row+1, column);
	  row++;
	  return 1;}
	else
	  return -1;}}
    if(row == 1 || row == 2){ 
      if(move == 'd'){
	if(checkEmpty(row-1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row-1, column);
	  row--;
	  return 1;}
	else
	  return -1;}}
    else
      return -1;}
  if(column == 3){
    if( move == 'u'){
      if(checkEmpty(row, 0) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 0);
	column = 0;
	return 1;}
      else
	return-1;}
    else if(move == 'd'){
      if(checkEmpty(row, 5) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 5);
	column = 5;
	return 1;}
      else
	return -1;}
    if(row == 0 || row == 1){
      if(move == 'r'){
	if(checkEmpty(row+1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row+1, column);
	  row++;
          return 1;}
	else
	  return -1;}}
    if(row == 1 || row == 2){ 
      if(move == 'l'){
	if(checkEmpty(row-1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row-1, column);
	  row--;
          return 1;}
	else
	  return -1;}}
    else
      return -1;}
  if(column == 4){
    if( move == 'u'){
      if(checkEmpty(row, 2) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 2);
	column = 2;
	return 1;}
      else 
	return -1;}
    else if(move == 'd'){
      if(checkEmpty(row, 7) == true){
	removeLocation(player, row, column);
	playLocation(player, row, 7);
	column = 7;
	return 1;}
      else
	return -1;}
    if(row == 0 || row == 1){
      if(move == 'l'){
	if(checkEmpty(row+1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row+1, column);
	  row++;
          return 1;}
	else
	  return -1;}}
    if(row == 1 || row == 2){ 
      if(move == 'r'){
	if(checkEmpty(row-1, column) == true){
	  removeLocation(player, row, column);
	  playLocation(player, row-1, column);
	  row--;
          return 1;}
	else
	  return -1;}}
    else
      return -1;} }


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

std::ostream& Board::errorMessage2(int error, std::ostream& output){
  if(error == 1)
    output << "Row number not in range 1-7\n";
  else if (error == 2)
    output << "Column number not in range 1-7\n";
  else if (error == 3)
    output << "Spot not on the board.\n";
  else if (error == 4)
    output << "No piece in that spot.\n";
  else if (error == 5)
    output << "Not your piece.\n"; }


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
  if(player != 1 && player != 2)
	return false;
  if(game[row][column] == 'e'){
    if(player == 1){
      game[row][column]= getPlayerSymbol(1);
      playCounter1++;}
    else{
      game[row][column]= getPlayerSymbol(2);
      playCounter2++;} 
    return true;}
  else
    return false; }

bool Board::removeLocation(int player, int row, int column){
if(player != 1 && player != 2)
  return false;
 if(game[row][column] != 'e'){
   if(player == 1){
     game[row][column] = 'e';
     playCounter1--;
     return true;}
   else{
     game[row][column] = 'e';
     playCounter2--;
     return true;} } }


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
