#include "ProgramController.h"


ProgramController::ProgramController() {
	game = nullptr;
}


ProgramController::~ProgramController() {
	delete game;
}


void ProgramController::run() {
	commandString = "";
	
	while (std::getline(std::cin, commandString)) {
		if (commandString.empty()) {
			
			std::getline(std::cin, commandString);
			if (!commandString.empty()) {
				commandString.erase(std::remove_if(commandString.begin(), commandString.end(), isspace), commandString.end());

				readAndExecuteCommand();

				continue;
			}
			

			/*std::getline(std::cin, commandString);
			if (!commandString.empty()) {
				commandString.erase(std::remove_if(commandString.begin(), commandString.end(), isspace), commandString.end());

				readAndExecuteCommand();

				continue;
			}*/

			/*std::getline(std::cin, commandString);
			if (!commandString.empty()) {
				commandString.erase(std::remove_if(commandString.begin(), commandString.end(), isspace), commandString.end());

				readAndExecuteCommand();

				continue;
			}*/

			if (commandString.empty()) {
				break;
			}
		}

		commandString.erase(std::remove_if(commandString.begin(), commandString.end(), isspace), commandString.end());

		readAndExecuteCommand();
	}
}


void ProgramController::readAndExecuteCommand() {
	if (commandString == "LOAD_GAME_BOARD") {
		delete game;
		
		game = new Game();
	}
	else if (commandString == "PRINT_GAME_BOARD") {
		game->printBoardInfo();
	}
	else if (commandString.substr(0, 7) == "DO_MOVE") {
		parseDoMoveCommand();
	}
	else {
		std::cerr << "INVALID INPUT";
	}
}


void ProgramController::parseDoMoveCommand() {
	std::string commandStringCopy = commandString;

	commandStringCopy.erase(0, 7);

	std::string fromPositionString = commandStringCopy.substr(0, 2);
	std::string toPositionString = commandStringCopy.substr(3, 2);

	std::tuple<int, int, int> fromPosition = game->convertAlphaNumToHex(fromPositionString);
	std::tuple<int, int, int> toPosition = game->convertAlphaNumToHex(toPositionString);

	int q = std::get<0>(fromPosition);
	int r = std::get<1>(fromPosition);
	int s = std::get<2>(fromPosition);
	
	int q2 = std::get<0>(toPosition);
	int r2 = std::get<1>(toPosition);
	int s2 = std::get<2>(toPosition);

	std::cerr << fromPositionString << " " << q << " " << r << " " << s << std::endl;
	std::cerr << toPositionString  << " " << q2 << " " << r2 << " " << s2 << std::endl;
	
	//game->move(fromPositionRow, fromPositionColumn, toPositionRow, toPositionColumn);
}
