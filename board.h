#ifndef BOARD_H
#define BOARD_H
#include <iostream>

class Board{
public:
	std::ostream& display(std::ostream&);
	Board();
	std::ostream& displayRules(std::ostream&);
	std::ostream& getMove(int, std::ostream&);
	void advancePhase(){phase++;}
	int getPhase(){return phase;}
	bool play(int, int, int);
private:
	void spotConverter(int&, int&);
	int checkValues(int, int);
	bool checkValid(int, int);
	char game[3][8];
	int phase;
	bool checkEmpty(int row, int column){if (game[row][column]=='e')return true; else return false;}
	std::ostream& printPiece(int, int, std::ostream&);
	bool playLocation(int, int, int);
};


#endif
