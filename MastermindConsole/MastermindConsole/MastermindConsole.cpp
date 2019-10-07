#include <iostream>
#include <conio.h>
#include "MastermindConsole.h"
#include <time.h>

std::string secretCode[4]; //Array with the Secret code
std::string colours[8] = { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange" }; //All the colours
std::string titleOptions[2][3] = { { "->", ".", "." }, {"Start", "Help", "Leave"} };
bool arrowPosition[3] = { true, false, false };
//Colours are Yellow, Red, Blue, Green, Brown, Black, Gray/White, 

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
	RandomiseColours(); //Function to randomise the colours
	RenderTitle(); //Renders the Ascii Art Title
	ArrowKeyPress();
		
	return 0; //Ends the program By returning zero to main
}

void ArrowKeyPress() //Checking if the key was pressed
{
	int c = 0;
	while (1) //Moving the arrow
	{
		c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			if (!(arrowPosition[0] == true)) //So the Arrow can't go off screen up
			{
				MoveArrow(-1);
			}
			break;
		case KEY_DOWN:
			if (!(arrowPosition[2] == true)) //so the Arrow cant go offscreen down
			{
				MoveArrow(1);
			}
			break;
		default:
			break;
		}
		if (false) 
		{
		
		}
	}
}

void MoveArrow(int positiveNegative)
{
	for (int i = 0; i < 3; i++)
	{
		if (arrowPosition[i])
		{
			for (int k = 0; k < 3; k++)
			{
				titleOptions[0][k] = ".";
			}
			titleOptions[0][i + positiveNegative] = "->";
			std::cout << "\n";
			arrowPosition[i] = false;
			arrowPosition[i + positiveNegative] = true;
			RenderTitle();
			break;
		}
	}
}

void RenderTitle()
{
	system("cls");
	std::string title[6] = { "  __  __              _               __  __  _             _ ",
		" |  \\/  |            | |             |  \\/  |(_)           | |",
		" | \\  / |  __ _  ___ | |_  ___  _ __ | \\  / | _  _ __    __| |",
		" | |\\/| | / _` |/ __|| __|/ _ \\| '__|| |\\/| || || '_ \\  / _` |",
		" | |  | || (_| |\\__ \\| |_|  __/| |   | |  | || || | | || (_| |",
		" |_|  |_| \\__,_||___/ \\__|\\___||_|   |_|  |_||_||_| |_| \\__,_|" };


	for (int i = 0; i < 6; i++)
	{
		std::cout << title[i] << "\n";
	}

	std::cout << "\n\n\t\t\t Select An option" << "\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << titleOptions[0][i] << titleOptions[1][i];
		std::cout << "\n";

	}
}

void RandomiseColours()
{
	srand(time(0));
	for (int i = 0; i < 4; i++) //four being the length of the secret code
	{
		int randomNum = std::rand() % 8; //Eight colours
		secretCode[i] = colours[randomNum];
	}
}


