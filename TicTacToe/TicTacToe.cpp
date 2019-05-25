#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Exeptions.h"

bool TicTacToe::isWin()
{
	if (board_->isRinRow(r_)) 
		return true;
	else
		return false;
}

player TicTacToe::play()
{
	player_ = randStartPlayer();

	std::cout << "Zaczyna symbol: " << (char)player_ << std::endl;

	board_->display();

	while (true)
	{
		if (board_->isFull()) 
			throw FULL_BOARD_EXEPTION;
		std::cout << "Tura gracza: " << (char)player_ << std::endl;
		move(player_);
		system("CLS");
		board_->display();
		if (isWin()) break;
		changeTurn();
	}
	return player_;
}

player TicTacToe::randStartPlayer()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2 + 1;
	if (i == 1)
		return player::X;
	else
		return player::O;
}

void TicTacToe::changeTurn()
{
	player_ == player::X ? player_ = player::O : player_ = player::X;
}

void TicTacToe::move(player p)
{
	if (player_ == player::X)
	{
		computerMove();
		return;
	}
	unsigned int x, y;
	std::cout << "Podaj wspolrzedne (x,y): ";
	bool isExeption;
	do
	{
		std::cin >> x >> y;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		isExeption = false;
		try
		{
			board_->markO(x, y);
		}
		catch (int exeption)
		{
			switch (exeption)
			{
			case INVALID_INDEX_EXEPTION:
			{
				std::cout << "Nieprawidlowe wpolrzedne. Podaj jeszcze raz: ";
				break;
			}
			case FULL_BOARD_EXEPTION:
			{
				std::cout << "Plansza zapelniona. KONIEC.";
				break;
			}
			case FIELD_OCCUPIED_EXEPTION:
			{
				std::cout << "Pole zajete -> wybierz inne pole. Podaj wspolrzedne: ";
				break;
			}
			default: break;
			}
			isExeption = true;
		}
	} while (isExeption);
}

void TicTacToe::computerMove()
{
	Board currentBoard = Board(*board_);
	Computer* com = new Computer(currentBoard, r_, player::X, player::O);
	unsigned int* optimalXY;
	optimalXY = com->optimalMove();
	//board_->display();
	board_->markX(optimalXY[0], optimalXY[1]);
	//board_->display();
	delete com;
}

TicTacToe::TicTacToe(unsigned int size, unsigned int row)
{
	if (row<0 or row>size)
		throw INVALID_MARKS_IN_ROW_EXEPTION;
	board_ = new Board(size);
	r_ = row;
}

TicTacToe::~TicTacToe()
{
}
