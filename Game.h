#pragma once

void checkPosition();

void checkColour();

void game();

void ButtonDownRight();

void ArrowSelection(bool  selectedOptionColour[8], std::string  guess[4], std::string  colourMenu[2][8]);

void ButtonDownLeft();

void PrintBoard();

void renderVerifier();

void renderGuess();

void MoveArrowColour(int positiveNegative, int sizeOfArray, bool arrowPosition[], std::string a[2][8]);