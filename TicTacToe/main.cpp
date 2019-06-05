
#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Board.h"
#include "TicTacToe.h"
#include "Exeptions.h"


int main()
{

	unsigned int n,r;
	
	bool isExeption;
	std::cout << "Podaj rozmiar planszy (n) oraz liczbe znakow w rzedzie potrzebna do wygranej (r): ";
	TicTacToe* game = new TicTacToe();
	do {
		std::cin >> n >> r;
		isExeption = false;
		try { game = new TicTacToe(n, r); }
		catch(int exeption)
		{
			if (exeption == INVALID_MARKS_IN_ROW_EXEPTION)
			{
				std::cout << "Niepoprawna liczba znakow w rzedzie. Podaj jeszcze raz: ";
				isExeption = true;
			}
			if (exeption == INVALID_SIZE_EXEPTION)
			{
				std::cout << "Niepoprawny rozmiar. Podaj jeszcze raz: ";
				isExeption = true;
			}
		}
	} while (isExeption);


	try 
	{
		game->play();
	}
	catch(...)
	{
		system("PAUSE");
	}

	system("PAUSE");
	return 1;
}