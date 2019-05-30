#pragma once

#include <algorithm>

#include "Board.h"
#include "PLayer.h"

class TicTacToe
{
private:
	Board* board_;
	unsigned int r_;
	player player_ = player::O;
	player computer_ = player::X;

	player currentPlayer_;
	player winner_;

	bool isDraw_ = true;

private:
	
	inline bool isWin();
	inline void changeTurn();

	void move(player p);
	void computerMove();
	void playerMove();

	int minmax_computer(Board board, unsigned int depthLevel, int alpha, int beta);
	int minmax_player(Board board, unsigned int depthLevel, int alpha, int beta);
	
	void randStartPlayer();
	void randSymbols();

public:

	void init();
	void play();
	player getWinner() { return currentPlayer_; }
	bool isDraw() { return isDraw_; }
	
	TicTacToe() {};
	TicTacToe(unsigned int size, unsigned int row);
	~TicTacToe();
};

