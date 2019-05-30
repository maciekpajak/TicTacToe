#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Exeptions.h"

bool TicTacToe::isWin()
{
	return board_->isRinRow(r_) ? true : false; 
}

void TicTacToe::init()
{
	randStartPlayer();
	std::cout << "Zaczyna symbol: " << (char)currentPlayer_ << std::endl;
	board_->display();
}

void TicTacToe::play()
{
	init();

	while (!board_->isFull())
	{
		std::cout << "Tura gracza: " << (char)currentPlayer_ << std::endl;
		move(currentPlayer_);
		system("CLS");
		board_->display();
		if (isWin())
		{
			winner_ = currentPlayer_;
			isDraw_ = false;
			break;
		}
		changeTurn();
	}
}

void TicTacToe::randStartPlayer()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2 + 1;
	if (i == 1)
		currentPlayer_ = player::X;
	else
		currentPlayer_ = player::O;
}

void TicTacToe::randSymbols()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2 + 1;
	if (i == 1)
	{
		player_ = player::X;
		computer_ = player::O;
	}
	else
	{
		player_ = player::O;
		computer_ = player::X;
	}
}

void TicTacToe::changeTurn()
{
	currentPlayer_ == computer_ ? currentPlayer_ = player_ : currentPlayer_ = computer_;
}

void TicTacToe::move(player p)
{
	p == computer_ ? computerMove() : playerMove();
}

int TicTacToe::minmax_computer(Board board, unsigned int depthLevel, int alpha, int beta)
{
	if (board.isRinRow(r_)) return -1;
	if (board.isFull()) return 0;
	
	for (unsigned int x = 0; x < board.getSize(); x++)
	{
		for (unsigned int y = 0; y < board.getSize(); y++)
		{
			if (board.isFieldOccupied(x, y))
				continue;

			Board newBoard = Board(board);
			newBoard.mark(computer_, x, y);

			alpha = std::max(alpha, minmax_player(newBoard, depthLevel + 1, alpha, beta));
			if (alpha == 1) return alpha;
			if (alpha >= beta) return beta;
		}
	}

	return alpha;

}

int TicTacToe::minmax_player(Board board, unsigned int depthLevel, int alpha, int beta)
{
	if (board.isRinRow(r_)) return 1;
	if (board.isFull()) return 0;

	for (unsigned int x = 0; x < board.getSize(); x++)
	{
		for (unsigned int y = 0; y < board.getSize(); y++)
		{
			if (board.isFieldOccupied(x, y))
				continue;

			Board newBoard = Board(board);
			newBoard.mark(player_, x, y);

			beta = std::min(beta, minmax_computer(newBoard, depthLevel + 1, alpha, beta));
			if (beta == -1) return beta;
			if (alpha >= beta) return alpha;

		}
	}
	return beta;
}

void TicTacToe::computerMove()
{
	Board currentBoard = Board(*board_);
	unsigned int optimalXY[2] = { 0,0 };
	int maximum = -1;
	for (unsigned int x = 0; x < currentBoard.getSize(); x++)
	{
		for (unsigned int y = 0; y < currentBoard.getSize(); y++)
		{
			Board newBoard = Board(currentBoard);
			if (currentBoard.isFieldOccupied(x, y))
				continue;
			newBoard.mark(computer_, x, y);

			int tmp = minmax_player(newBoard, 1, -1, 1);
			if (tmp >= maximum)
			{
				optimalXY[0] = x;
				optimalXY[1] = y;
				maximum = tmp;
			}
			if (maximum == 1) 
			{ 
				board_->mark(computer_, optimalXY[0], optimalXY[1]);
				return; 
			}
		}
	}
	board_->mark(computer_,optimalXY[0], optimalXY[1]);
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
			board_->mark(player_, x, y);
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

