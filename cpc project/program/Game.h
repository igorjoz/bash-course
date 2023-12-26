#pragma once


#include "Board.h"


class Game
{
private:
	Board* board;
	
	int boardSize = 0;
	int piecesInLineToTriggerCapture = 0;
	
	int whitePiecesQuantity = 0;
	int blackPiecesQuantity = 0;
	
	int whitePiecesLeft = 0;
	int blackPiecesLeft = 0;

	char initialPlayerCharacter = 'W';

	bool isWhitePlayerTurn = true;

public:
	Game();
	~Game();

	void readGameSettings();

	void checkBoardAfterReading();

	std::tuple<int, int, int> convertAlphaNumToHex(const std::string& alphaNumCoord);

	void printBoardInfo();
};

