#include <iostream>
#include "GDWMastermind.h"
#include "Game.h"
#include <conio.h> 
#include <windows.h>
#include <time.h>


#define KEY_UP 72 
#define KEY_DOWN 80 
#define KEY_LEFT 75 
#define KEY_RIGHT 77 

HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
std::string space = "";
std::string indent = "		";
std::string next = "\n";
std::string colours[8] = { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange" };
std::string secretCodeCopy[4];
std::string colourMenu[2][8] = { {"->", ".",".",".",".",".",".","."},  { "Yellow", "Red", "Blue", "Green", "Brown", "Black", "White", "Orange"} };
std::string guess[5] = { "*", "_","_","_", "" };
std::string selection[4] = {};
std::string verifier[4] = {};
bool isContinue = false; // is for to check for if the arrow should be over the continue string and shouldn't allow for any up or down movement
bool selectedOptionColour[8] = { true, false, false, false, false, false, false, false };



void game()
{
	srand(time(NULL));
	for (int i = 0; i < 4; i++) //four being the length of the secret code 
	{
		int randomNum = std::rand() % 8; //Eight colours 
		secretCodeCopy[i] = colours[randomNum];
	}


	std::string copy[4];
	/*//porting the secret code to this cpp
	for (int i = 0; i < 4; i++)
	{
		secretCodeCopy[i] = copy[i];
	}*/

	system("cls");
	//menu items
	PrintBoard();
	ArrowSelection(selectedOptionColour, guess, colourMenu);

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
			if (!(selectedOptionColour[0] == true) && !isContinue) //So the Arrow can't go off screen up  isContinue is to know if the Continue prompt is up and not to allow cursor mvment
			{
				MoveArrowColour(-1, 8, selectedOptionColour, colourMenu);
				PrintBoard();
			}
			break;
		case KEY_DOWN:
			if (!(selectedOptionColour[7] == true) && !isContinue) //so the Arrow cant go offscreen down and isContinue is to know if the Continue prompt is up and not to allow cursor mvment
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
	for (int i = 0; i < 5; i++)
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
//moves the arrow up and down in the string and the bool arrays
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
	if (isContinue)
	{
		//if the continue prompt is up then verify the code
		checkPosition();
		checkColour();
		renderGuess();
		renderVerifier();
		int stop = 0;

	}
	//loop to add the selected 
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
					else
					{
						guess[k + 1] = "->Confirm?";
						isContinue = true;
						for (int k = 0; k < 8; k++)
						{	
							colourMenu[0][k] = ".";
						}
					}
					guess[k] = colourMenu[1][i];
					break;
				}

			}
			break;
		}
	}


}

void ButtonDownLeft()  //Left button press to remove the text and put a * and _
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
					guess[k + 1] = "";
					isContinue = false; //continue prompt is no longer there
					MoveArrowColour(0, 8, selectedOptionColour, colourMenu); //draw the arrow back where it was last
				}
			}
			break;
		}
	}
}
void checkPosition()
{
	for (int i = 0; i < 4; i++)
	{
		if (guess[i] == secretCodeCopy[i])
		{
			verifier[i] = "Red";
		}
		else
		{
			verifier[i] = "Empty";
		}
	}
}

void checkColour()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (guess[i] == secretCodeCopy[j] && verifier[i] == "Empty")
			{
				verifier[i] = "White";
			}
		}
	}
}

void renderVerifier()
{
	for (int i = 0; i < 4; i++)
	{
		if (verifier[i] == "Red")
		{
			//Blue - 1 , Green - 10, Light BLue - 11 , Red - 12 , White - 15
			SetConsoleTextAttribute(colour, 12);
			std::cout << "\n	 _ ";
			std::cout << "\n	( )";
			std::cout << "\n	|/ ";
		}
		else if (verifier[i] == "White")
		{
			SetConsoleTextAttribute(colour, 15);
			std::cout << "\n	 _ ";
			std::cout << "\n	( )";
			std::cout << "\n	|/ ";
		}
		
	}
}

void renderGuess()
{

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			space = "";
			
		}
		else if (i == 1)
		{
			space = "	";
			
		}
		else if (i == 2)
		{
			space = "		";
			
		}
		else
		{
			space = "			";
			
		}


		if (guess[i] == "Red")
		{
			SetConsoleTextAttribute(colour, 12);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Blue")
		{
			SetConsoleTextAttribute(colour, 11);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Green")
		{
			SetConsoleTextAttribute(colour, 10);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Yellow")
		{
			SetConsoleTextAttribute(colour, 14);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Orange")
		{
			SetConsoleTextAttribute(colour, 6);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "White")
		{
			SetConsoleTextAttribute(colour, 15);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Brown")
		{
			SetConsoleTextAttribute(colour, 6);
			std::cout << next << "	 _ \n	(_)";
		}
		else if (guess[i] == "Black")
		{
			SetConsoleTextAttribute(colour, 16);
			std::cout << next << "	 _ \n	(_)";
		}
	}

	
}
