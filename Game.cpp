#include <iostream>
#include "GDWMastermind.h"
#include "Game.h"
#include <conio.h> 

#define KEY_UP 72 
#define KEY_DOWN 80 
#define KEY_LEFT 75 
#define KEY_RIGHT 77 

std::string colourMenu[2][8] = { {"->", ".",".",".",".",".",".","."},  { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange"} };
std::string guess[4] = { "*", "_","_","_" };
bool selectedOptionColour[8] = { true, false, false, false, false, false, false, false };



void game() 
{
	system("cls");
	//menu items

	PrintBoard();
	ArrowSelection(selectedOptionColour, guess,colourMenu);

}
void ArrowSelection(bool  selectedOptionColour[8], std::string  guess[4], std::string  colourMenu[2][8])
{
	//menu selction thing
	bool running = true;
	int x = 0;
	while (running) //Moving the arrow 
	{
		x = 0;
		switch ((x = _getch()))
		{
		case KEY_UP:
			if (!(selectedOptionColour[0] == true)) //So the Arrow can't go off screen up 
			{
				MoveArrowColour(-1, 8, selectedOptionColour, colourMenu);
				PrintBoard();
			}
			break;
		case KEY_DOWN:
			if (!(selectedOptionColour[7] == true)) //so the Arrow cant go offscreen down 
			{
				MoveArrowColour(1, 8, selectedOptionColour, colourMenu);
				PrintBoard();
			}
			break;
		case KEY_RIGHT:
			ButtonDownRight();
			PrintBoard();
			break;
		case KEY_LEFT:
			ButtonDownLeft();
			PrintBoard();
			break;
		default:
			break;
		}

	}
}
void PrintBoard()
{
	system("cls");
	std::cout << "Insert your guess\n";
	//prints the colours that the player has selected
	for (int i = 0; i < 4; i++)
	{
		std::cout << guess[i] << "\t";
	}
	std::cout << "\n";
	//prints out the colours menu for the plaer to select
	for (int i = 0; i < 8; i++)
	{
		std::cout << colourMenu[0][i] << colourMenu[1][i];
		std::cout << "\n";

	}
}
void MoveArrowColour(int positiveNegative, int sizeOfArray, bool arrowPosition[], std::string option[2][8])
{
	for (int i = 0; i < sizeOfArray; i++)
	{
		if (arrowPosition[i])
		{
			for (int k = 0; k < sizeOfArray; k++)
			{
				option[0][k] = ".";
			}
			option[0][i + positiveNegative] = "->";
			std::cout << "\n";
			arrowPosition[i] = false;
			arrowPosition[i + positiveNegative] = true;
			break;
		}
	}
}
void ButtonDownRight()
{
	for (int i = 0; i < 8; i++)
	{
		if (selectedOptionColour[i])
		{
			for (int k = 0; k < 4; k++)
			{
				if (guess[k] == "*")
				{
					if (k != 3)
					{
						guess[k + 1] = "*";
					}
					guess[k] = colourMenu[1][i];
					break;
				}

			}
			break;
		}
	}


}

void ButtonDownLeft() 
{
	for (int i = 0; i < 8; i++)
	{
		if (selectedOptionColour[i])
		{
			for (int k = 0; k < 4; k++)
			{
				if (guess[k] == "*")
				{
					if (k != 0)
					{
						guess[k - 1] = "*";
						guess[k] = "_";
					}
					break;
				}
				else if (k == 3)
				{
					guess[k] = "*";
				}
			}
			break;
		}
	}
}

