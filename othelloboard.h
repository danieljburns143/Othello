// othelloboard.h
// Daniel Burns

#include <vector>
#include <iostream>

#ifndef OTHELLOBOARD_H
#define OTHELLOBOARD_H

class OthelloBoard {
	friend std::ostream& operator<<(std::ostream&, const OthelloBoard&); // method to display board
public:
	OthelloBoard(); // default constructor
	OthelloBoard(int, int); // construcot with two parameters
	~OthelloBoard(); // destructor
	void setBoardSize(int, int); // method to set size of othelloboard
	void setBoardCharacter(char, int, int); // method to set the character value of an element
	int getRowSize(); // method to return row size
	int getColumnSize(); // method to return column size
	bool gameFinished(); // method to check if game is finished, i.e., no more moves are possible
	char getCharacter(int, int); // method to return character of element on board
	bool captureLeft(int, int); // method to return if you can capture opponent's character to left
	bool captureRight(int, int); // method to return if you can caputre opponent's character to right
	bool captureUp(int, int); // method to return if you can capture opponent's character up
	bool captureDown(int, int); // method to return if you can capture opponent's character down
	bool captureUpLeft(int, int); // method to return if you can capture opponent's character up left
	bool captureUpRight(int, int); // method to return if you can capture opponent's character up right
	bool captureDownLeft(int, int); // method to return if you can capture opponent's character down left
	bool captureDownRight(int, int); // method to return if you can capture opponent's character down right
private:
	int rowsize{8};
	int columnsize{8};
	std::vector< std::vector<char> > board{};
};

#endif
