#pragma once

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <vector>

#include "Exeptions.h"
#include "Board.h"
#include "PLayer.h"
#include "SFML/Graphics.hpp"

#define PLAYER_WIN_VALUE -10
#define COMPUTER_WIN_VALUE 10
#define DRAW 0 
#define MAX_DEPTH_LEVEL 5

#define SCREEN_X 600
#define SCREEN_Y 600
#define FIELD_SIZE 100
#define SYMBOL_SIZE 100
#define MENU_BAR 50

class TicTacToe
{
private:
	Board* board_;
	unsigned int r_;
	unsigned int size_;
	player player_ = player::O;
	player computer_ = player::X;

	player currentPlayer_;
	player winner_;
	
	unsigned int maxDepthLevel_ = 1;
	int howManyEmpty_;


private:
	
	inline bool isWin();
	inline void changeTurn();

	void move(player p);
	void computerMove();
	void playerMove();

	bool graphicPlayerMove(sf::Vector2i mousePosition, sf::RenderWindow &screen);
	bool graphicComputerMove(sf::RenderWindow &screen);

	int h(Board board);

	int minmax_computer(Board board, unsigned int depthLevel, int alpha, int beta);
	int minmax_player(Board board, unsigned int depthLevel, int alpha, int beta);
	
	void randStartPlayer();
	void randSymbols();



public:

	void init(sf::RenderWindow &screen);
	void play();
	void reset();


	player getWinner() { return currentPlayer_; }
	
	TicTacToe(){};
	TicTacToe(unsigned int size, unsigned int row);
	~TicTacToe();
};

