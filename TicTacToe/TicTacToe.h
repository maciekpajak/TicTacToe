#pragma once
#include "Board.h"
#include "Move.h"

class TicTacToe
{
private:
	Board* board_;
	unsigned int r_;
	move move_;

public:

	bool isWin();

	move play();

	bool isRInRow(unsigned int y);
	bool isRInColumn(unsigned int x);
	bool isRInDiagonal() { return false; }

	void changeTurn();
	void playerMove();

	TicTacToe() {};
	TicTacToe(unsigned int size, unsigned int row);
	~TicTacToe();
};

