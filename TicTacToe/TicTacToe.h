#pragma once
#include "Board.h"
#include "PLayer.h"
#include "Computer.h"

class TicTacToe
{
private:
	Board* board_;
	unsigned int r_;
	player player_;

public:

	bool isWin();

	player play();
	player randStartPlayer();

	void changeTurn();

	void move(player p);
	void computerMove();

	TicTacToe() {};
	TicTacToe(unsigned int size, unsigned int row);
	~TicTacToe();
};

