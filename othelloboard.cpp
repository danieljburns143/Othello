// othelloboard.cpp
// Daniel Burns

#include <iostream>
#include <iomanip>
#include <vector>
#include "othelloboard.h"
using namespace std;

// default constructor
OthelloBoard::OthelloBoard() {
	setBoardSize(rowsize, columnsize);
	board[(board.size()/2)-1][(board.size()/2)-1] = 'X';
	board[board.size()/2][board.size()/2] = 'X';
	board[(board.size()/2)-1][board.size()/2] = 'O';
	board[board.size()/2][(board.size()/2)-1] = 'O';
}

// destructor
OthelloBoard::~OthelloBoard() {}

// friend overloaded operator <<
ostream& operator<<(ostream& output, const OthelloBoard& gameboard) {
	cout << " ";
	for (int i{0}; i < gameboard.board.size(); i++) {
		cout << setw(2) << i;
	}
	cout << endl;
	for (int i{0}; i < gameboard.board.size(); i++) {
		cout << i;
		for (int j{0}; j < gameboard.board[i].size(); j++) {
			cout << setw(2) << gameboard.board[i][j];
		}
		cout << endl;
	}
	return output;
}

// method to return row size
int OthelloBoard::getRowSize() {
	return rowsize;
}

// method to return column size
int OthelloBoard::getColumnSize() {
	return columnsize;
}

// method to set the size of the board
void OthelloBoard::setBoardSize(int row, int column) {
	board.resize(row);
	for (int i{0}; i < board.size(); i++) {
		board[i].resize(column, '.');
	}
}

// method to set character for a certain element on the board
void OthelloBoard::setBoardCharacter(char letter, int row, int column) {
	board[row][column] = letter;
}

// method to check if game is finished, i.e., if no more moves are possible
bool OthelloBoard::gameFinished() {
	for (int i{0}; i < board.size(); i++) {
		for (int j{0}; j < board[i].size(); j++) {
			if (board[i][j] == '.') { return 0; }
		}
	}
	return 1;
}

// method to return character of element on board
char OthelloBoard::getCharacter(int row, int column) {
	return board[row][column];
}

// method to return if move captures pieces to the left
bool OthelloBoard::captureLeft(int row, int column) {
	if ((column-2 >= 0) && (board[row][column-1] != '.' && board[row][column-1] != board[row][column]) && (board[row][column-2] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces to the right
bool OthelloBoard::captureRight(int row, int column) {
	if ((column+2 < columnsize) && (board[row][column+1] != '.' && board[row][column+1] != board[row][column]) && (board[row][column+2] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces up
bool OthelloBoard::captureUp(int row, int column) {
	if ((row-2 >= 0) && (board[row-1][column] != '.' && board[row-1][column] != board[row][column]) && (board[row-2][column] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces down
bool OthelloBoard::captureDown(int row, int column) {
	if ((row+2 < rowsize) && (board[row+1][column] != '.' && board[row+1][column] != board[row][column]) && (board[row+2][column] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces up left
bool OthelloBoard::captureUpLeft(int row, int column) {
	if ((row-2 >= 0) && (column-2 >= 0) && (board[row-1][column-1] != '.' && board[row-1][column-1] != board[row][column]) && (board[row-2][column-2] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces up right
bool OthelloBoard::captureUpRight(int row, int column) {
	if ((row-2 >= 0) && (column+2 < columnsize) && (board[row-1][column+1] != '.' && board[row-1][column+1] != board[row][column]) && (board[row-2][column+2] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces down left
bool OthelloBoard::captureDownLeft(int row, int column) {
	if ((row+2 < rowsize) && (column-2 >= 0) && (board[row+1][column-1] != '.' && board[row+1][column-1] != board[row][column]) && (board[row+2][column-2] == board[row][column])) {
		return 1;
	}
	return 0;
}

// method to return if move captures pieces down right
bool OthelloBoard::captureDownRight(int row, int column) {
	if ((row+2 < rowsize) && (column+2 < columnsize) && (board[row+1][column+1] != '.' && board[row+1][column+1] != board[row][column]) && (board[row+2][column+2] == board[row][column])) {
		return 1;
	}
	return 0;
}
