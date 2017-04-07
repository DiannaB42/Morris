#ifndef BOARD_H
#define BOARD_H
#include <iostream>

class Board{
public:
	std::ostream& display(std::ostream&);
	Board();
	std::ostream& displayRules(std::ostream&);
	std::ostream& getMove1(int, std::ostream&);
	int getPhase(){return phase;}
	char getPiece(int row, int column){return game[row][column];}
	bool play(int, int, int);
	int countPieces(int);
	std::ostream& errorMessage(int, std::ostream&);
	std::ostream& errorMessageMills(int, std::ostream&);
	int getMaxPieces(){return 9;}
private:
	int playCounter1;
	int playCounter2;
	void advancePhase(){phase++;}
	void spotConverter(int&, int&);
	int checkValues(int, int);
	int checkValuesMills(int, int, int);
	bool checkValid(int, int);
	bool removePiece(int, int);
	int checkMills(int, int, int);
	char getPlayerSymbol(int);
	char game[3][8];
	int phase;
	bool checkEmpty(int row, int column){if (game[row][column]=='e')return true; else return false;}
	std::ostream& printPiece(int, int, std::ostream&);
	bool playLocation(int, int, int);
};


#endif
