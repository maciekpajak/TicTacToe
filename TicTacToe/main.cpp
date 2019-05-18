#include <iostream>
#include <Windows.h>

#include "Board.h"

int main()
{
	int n;
	std::cout << "Podaj rozmiar planszy: ";
	std::cin >> n;
	std::cin.clear();
	std::cin.ignore(1000, '\n');

	Board B = Board(n);

	int x, y;
	for (int i = 0; i < n*n; i++)
	{
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
				B.markO(x, y);
			}
			catch (int exeption)
			{
				switch (exeption)
				{
				case INVALID_INDEX_EXEPTION:
					{
					std::cout << "Nieprawidlowe wpolrzedne. Podaj jeszcze raz: ";
					std::cin.clear();
					break;
					}
				case FULL_BOARD_EXEPTION:
					{
					std::cout << "Plansza zapelniona. KONIEC.";
					system("PAUSE");
					return 1;
					}
				case FIELD_OCCUPIED_EXEPTION:
					{
					std::cout << "Pole zajete, wybierz inne pole. Podaj wspolrzedne: ";
					std::cin.clear();
					break;
					}
				default: break;
				}
				isExeption = true;
			}
		} while (isExeption);
		B.display();
	}

	system("PAUSE");
	return 1;
}