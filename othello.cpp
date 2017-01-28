// othello.cpp
// Daniel Burns
// Othello - Part 1

#include <iostream>
#include <array>
#include "othelloboard.h"
using namespace std;

void iterateBoard(int, int, OthelloBoard&, int); // prototype to iterate the board with the rules
bool connectedToOtherPiece(int, int, OthelloBoard&); // prototype to make sure move is connected to another piece

int main () {
	int row, column;
	int turn{1};
	system("clear");
	OthelloBoard gameboard;
	cout << gameboard;
	cout << "\nPlayer X goes first\n";
	while (gameboard.gameFinished() == 0) {
		((turn % 2) == 1) ? cout << "Player X:\n" : cout << "Player O:\n";
		cout << "---------\n\n";
		cout << "Enter X Coordinate: ";
		cin >> column;
		while (cin.good() != 1 || column < 0 || column >= gameboard.getColumnSize()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input.. Please re-enter X coordinate: ";
			cin >> column;
		}
		cout << "Enter Y Coordinate: ";
		cin >> row;
		while (cin.good() != 1 || row < 0 || row >= gameboard.getRowSize()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input.. Please re-enter Y coordinate: ";
			cin >> row;
		}
		if (gameboard.getCharacter(row, column) != '.') {
			cout << "\nThere is already a piece there.. Please re-enter X and Y coordinates\n" << endl;
			continue;
		}
		if (connectedToOtherPiece(row, column, gameboard) != 1) {
			cout << "\nPiece must be connected to another piece.. Please re-enter X and Y coordinates\n" << endl;
			continue;
		}
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row, column) : gameboard.setBoardCharacter('O', row, column);
		iterateBoard(row, column, gameboard, turn);
		turn++;
		system("clear");
		cout << gameboard << endl << endl;
	}
	int xcount{0};
	int ocount{0};
	for (int i{0}; i < gameboard.getRowSize(); i++) {
		for (int j{0}; j < gameboard.getColumnSize(); j++) {
			if (gameboard.getCharacter(i, j) == 'X') { xcount++; }
			else if (gameboard.getCharacter(i, j) == 'O') { ocount++; }
		}
	}
	if (xcount > ocount) { cout << "Player X wins!\n"; }
	else if (xcount < ocount) { cout << "Player O wins!\n"; }
	else { cout << "It's a tie!\n"; }
	cout << "Thank you for playing" << endl << endl;
}

// function to iterate the board with the rules
void iterateBoard(int row, int column, OthelloBoard& gameboard, int turn) {
	if (gameboard.captureLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row, column-1) : gameboard.setBoardCharacter('O', row, column-1);
	}
	if (gameboard.captureRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row, column+1) : gameboard.setBoardCharacter('O', row, column+1);
	}
	if (gameboard.captureUp(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column) : gameboard.setBoardCharacter('O', row-1, column);
	}
	if (gameboard.captureDown(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column) : gameboard.setBoardCharacter('O', row+1, column);
	}
	if (gameboard.captureUpLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column-1) : gameboard.setBoardCharacter('O', row-1, column-1);
	}
	if (gameboard.captureUpRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column+1) : gameboard.setBoardCharacter('O', row-1, column+1);
	}
	if (gameboard.captureDownLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column-1) : gameboard.setBoardCharacter('O', row+1, column-1);
	}
	if (gameboard.captureDownRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column+1) : gameboard.setBoardCharacter('O', row+1, column+1);
	}
}

// function to check if piece is connected to another piece
bool connectedToOtherPiece(int row, int column, OthelloBoard& gameboard) {
	int checkrow{row}, checkcolumn{column};
	for (int i{-1}; i <= 1; i++) {
		for (int j{-1}; j <= 1; j++) {
			if ((checkrow+i < gameboard.getRowSize()) && (checkrow+i >= 0) && (checkcolumn+j < gameboard.getColumnSize()) && (checkcolumn+j >= 0)) {
				if (gameboard.getCharacter(checkrow+i, checkcolumn+j) != '.') { return 1; }
			}
		}
	}
	return 0;
}
