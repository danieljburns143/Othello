// othello_ai.cpp
// Daniel Burns
// Othello - Part 1

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "othelloboard.h"
using namespace std;

int iterateTempBoard(int, int, OthelloBoard&, int); // prototype to iterate the board AND return how many pieces were won
void iterateBoard(int, int, OthelloBoard&, int); // prototype to iterate the board with the rules
bool connectedToOtherPiece(int, int, OthelloBoard&); // prototype to make sure move is connected to another piece

int main () {
	srand(unsigned(time(0)));
	int difficulty;
	int row, column;
	int turn{1};
	system("clear");
	cout << "Enter difficulty from 1 - 3 (1: easiest, 3: hardest)..: ";
	cin >> difficulty;
	while (cin.good() != 1 || difficulty < 1 || difficulty > 3) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please enter a valid difficulty..: ";
		cin >> difficulty;
	}
	system("clear");
	OthelloBoard gameboard;
	cout << gameboard;
	cout << "\nHuman goes first\n";
	while (gameboard.gameFinished() == 0) {
		int computerrow, computercolumn;
		if ((turn % 2) == 0) {
			int pieceswon{0};
			int attempts{0};
			int temprow;
			int tempcolumn;
			int maxpieces{0};
			int computerrow, computercolumn;
			OthelloBoard tempboard;
			switch (difficulty) {
				case 1:
					computerrow = rand() % gameboard.getRowSize();
					computercolumn = rand() % gameboard.getColumnSize();
					while (gameboard.getCharacter(computerrow, computercolumn) != '.' || connectedToOtherPiece(computerrow, computercolumn, gameboard) != 1) {
						computerrow = rand() % gameboard.getRowSize();
						computercolumn = rand() % gameboard.getColumnSize();
					}
					cout << "Computer is thinking..." << endl;
					gameboard.setBoardCharacter('O', computerrow, computercolumn);
					iterateBoard(computerrow, computercolumn, gameboard, turn);
					turn++;
					usleep(1100000);
					system("clear");
					cout << gameboard << endl << endl;
					cout << "Computer placed piece at " << computercolumn << " x " << computerrow << endl << endl;
					break;
				case 2:
					// computer only places piece on gameboard if it flips over a piece, or if it has gone through every single available open space w/ no pieces flipped
					while (pieceswon == 0 && attempts < 400) {
						tempboard = gameboard;
						computerrow = rand() % tempboard.getRowSize();
						computercolumn = rand() % tempboard.getColumnSize();
						while (tempboard.getCharacter(computerrow, computercolumn) != '.' || connectedToOtherPiece(computerrow, computercolumn, tempboard) != 1) {
							computerrow = rand() % tempboard.getRowSize();
							computercolumn = rand() % tempboard.getColumnSize();
						}
						tempboard.setBoardCharacter('O', computerrow, computercolumn);
						pieceswon = iterateTempBoard(computerrow, computercolumn, tempboard, turn);
						attempts++;
					}
					cout << "Computer is thinking..." << endl;
					gameboard = tempboard;
					turn++;
					usleep(1100000);
					system("clear");
					cout << gameboard << endl << endl;
					cout << "Computer placed piece at " << computercolumn << " x " << computerrow << endl << endl;
					break;
				case 3:
					for (int i{0}; i < gameboard.getRowSize(); i++) {
						for (int j{0}; j < gameboard.getColumnSize(); j++) {
							tempboard = gameboard;
							if (tempboard.getCharacter(i, j) != '.' || connectedToOtherPiece(i, j, tempboard) != 1) {
								continue;
							}
							tempboard.setBoardCharacter('O', i, j);
							pieceswon = iterateTempBoard(i, j, tempboard, turn);
							if (pieceswon >= maxpieces) {
								maxpieces = pieceswon;
								temprow = i;
								tempcolumn = j;
							}
						}
					}
					cout << "Computer is thinking..." << endl;
					gameboard.setBoardCharacter('O', temprow, tempcolumn);
					iterateBoard(temprow, tempcolumn, gameboard, turn);
					turn++;
					usleep(1100000);
					system("clear");
					cout << gameboard << endl << endl;
					cout << "Computer placed piece at " << tempcolumn << " x " << temprow << endl;
					cout << "Computer flipped " << maxpieces << " pieces" << endl << endl;
					break;
				default:
					cout << "Error.. default case should not be reached" << endl;
					break;
			}
			continue;
		}
		cout << "Human's Turn:\n";
		cout << "-------------\n\n";
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
		gameboard.setBoardCharacter('X', row, column);
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
	if (xcount > ocount) { cout << "Human wins!\n"; }
	else if (xcount < ocount) { cout << "Computer wins!\n"; }
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

// function to iterate the board AND return number of pieces won
int iterateTempBoard(int row, int column, OthelloBoard& gameboard, int turn) {
	int pieceswon{0};
	if (gameboard.captureLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row, column-1) : gameboard.setBoardCharacter('O', row, column-1);
		pieceswon++;
	}
	if (gameboard.captureRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row, column+1) : gameboard.setBoardCharacter('O', row, column+1);
		pieceswon++;
	}
	if (gameboard.captureUp(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column) : gameboard.setBoardCharacter('O', row-1, column);
		pieceswon++;
	}
	if (gameboard.captureDown(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column) : gameboard.setBoardCharacter('O', row+1, column);
		pieceswon++;
	}
	if (gameboard.captureUpLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column-1) : gameboard.setBoardCharacter('O', row-1, column-1);
		pieceswon++;
	}
	if (gameboard.captureUpRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row-1, column+1) : gameboard.setBoardCharacter('O', row-1, column+1);
		pieceswon++;
	}
	if (gameboard.captureDownLeft(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column-1) : gameboard.setBoardCharacter('O', row+1, column-1);
		pieceswon++;
	}
	if (gameboard.captureDownRight(row, column)) {
		((turn % 2) == 1) ? gameboard.setBoardCharacter('X', row+1, column+1) : gameboard.setBoardCharacter('O', row+1, column+1);
		pieceswon++;
	}
	return pieceswon;
}
