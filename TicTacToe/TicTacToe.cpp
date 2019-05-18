#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Exeptions.h"

bool TicTacToe::isWin()
{
	for (int i = 0; i < board_->getSize(); i++)
	{
		if (isRInRow(i)) return true;
		if (isRInColumn(i)) return true;
	}
	return false;
}

move TicTacToe::play()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2;
	i == 0 ? move_ = move::firstPlayer : move_ = move::secondPlayer;
	std::cout << "Zaczyna gracz: " << (int)move_ << std::endl;
	board_->display();
	while (!isWin())
	{
		if (board_->isFull()) throw FULL_BOARD_EXEPTION;
		std::cout << "Tura gracza: " << (int)move_ << std::endl;
		playerMove();
		changeTurn();
		board_->display();
	}
	changeTurn();
	return move_;
}

bool TicTacToe::isRInRow(unsigned int y)
{
	if (y < 0 or y >= board_->getSize())
		throw INVALID_INDEX_EXEPTION;
	std::string row(r_, ' ');
	std::string rowX(r_, 'X');
	std::string rowO(r_, 'O');
	for (int i = 0; i < board_->getSize(); i++)
	{
		row[i % r_] = (*board_)(i, y);
		if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
	}
	return false;
}

bool TicTacToe::isRInColumn(unsigned int x)
{
	if (x < 0 or x>(board_->getSize() - 1))
		throw INVALID_INDEX_EXEPTION;
	std::string row(r_, ' ');
	std::string rowX(r_, 'X');
	std::string rowO(r_, 'O');
	for (int i = 0; i < board_->getSize(); i++)
	{
		row[i % r_] = (*board_)(x, i);
		if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
	}
	return false;
}

void TicTacToe::changeTurn()
{
	move_ == firstPlayer ? move_ = secondPlayer : move_ = firstPlayer;
}

void TicTacToe::playerMove()
{
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
			move_ == firstPlayer ? board_->markO(x, y) : board_->markX(x, y);
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
	if (row<0 or row>size)
		throw INVALID_MARKS_IN_ROW_EXEPTION;
	board_ = new Board(size);
	r_ = row;
}

TicTacToe::~TicTacToe()
{
}
