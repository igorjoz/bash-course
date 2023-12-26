#pragma once


#include <iostream>
#include <string>


#include "Game.h"
#include "Resources.h"


class ProgramController
{
private:
	Game* game;

	std::string commandString;
	
public:
	ProgramController();
	~ProgramController();

	void run();
	void readAndExecuteCommand();

	void parseDoMoveCommand();
};

