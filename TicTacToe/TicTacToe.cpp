#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


move TicTacToe::game()
{
	srand((unsigned int)time(NULL));
	return move::firstPlayer;
}

void TicTacToe::playerMove()
{

	if (move_ == firstPlayer)
		firstPlayerMove();
	if (move_ == secondPlayer)
		secondPlayerMove();
}

void TicTacToe::firstPlayerMove()
{
	unsigned int x, y;
	std::cout << "Podaj wspolrzedne O (x,y): ";
	bool isExeption;
	do
	{
		std::cin >> x >> y;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		isExeption = false;
		try
		{
			board_.markO(x, y);
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

TicTacToe::TicTacToe(unsigned int size, unsigned int row)
{
	board_ = Board(size);
	r_ = row;
}


TicTacToe::~TicTacToe()
{
}
