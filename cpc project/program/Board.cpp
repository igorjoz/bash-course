#include "Board.h"


Board::Board(int size, int piecesInLineToTriggerCapture) :
	size{ size },
	piecesInLineToTriggerCapture{ piecesInLineToTriggerCapture },
	totalEmptyPlaces{ 0 },
	whitePiecesPlaced{ 0 },
	blackPiecesPlaced{ 0 },
	spacesQuantity { size },
	hasPassedMiddleLine{ false },
	isCorrupted{ false },
	foundChainsQuantity{ 0 } {
}


void Board::read() {
	size--;

	int placesInHexagonInTotal = 3 * size * (size + 1) + 1;
	int height = 2 * size + 1;

	int newLineCount = 0;
	int placesCount = 0;
	std::string boardString = "";

	char character = getchar();
	character = getchar();

	while (newLineCount < height) {
		if (character == '\n' or character == EOF) {
			newLineCount++;
		}
		else if (character == '_' or character == 'W' or character == 'B') {
			boardString += character;
			placesCount++;
		}
		
		character = getchar();
	}

	if (placesCount != placesInHexagonInTotal) {
		std::cout << "WRONG_BOARD_ROW_LENGTH\n";
		isCorrupted = true;

		return;
	}

	int placeIndex = 0;

	for (int q = -size; q <= size; q++) {
		int r1 = std::max(-size, -q - size);
		int r2 = std::min(size, -q + size);

		for (int r = r1; r <= r2; r++) {
			character = boardString[placeIndex++];

			if (character == '_') {
				map.insert(Hex(q, r, -q - r));
				totalEmptyPlaces++;
			}
			else if (character == 'W') {
				map.insert(Hex(q, r, -q - r, true, true));
				whitePiecesPlaced++;
			}
			else {
				map.insert(Hex(q, r, -q - r, true, false));
				blackPiecesPlaced++;
			}
		}
	}

	size++;

	printWithIndices();
}


void Board::print() {
	for (int q = -size; q <= size; q++) {
		int r1 = std::max(-size, -q - size);
		int r2 = std::min(size, -q + size);

		handleSpacesWhileDrawing();

		for (int r = r1; r <= r2; r++) {
			auto hex = map.find(Hex(q, r, -q - r));
			
			if (hex != map.end()) {
				if (!hex->isOccupied) {
					std::cout << "_";
				}
				else if (hex->isWhite) {
					std::cout << "W";
				}
				else {
					std::cout << "B";
				}

				std::cout << " ";
			}
			else if (r != r1) {
				std::cout << "  ";
			}
		}

		std::cout << "\n";
	}
}


void Board::printWithIndices() {
	for (int q = -size; q <= size; q++) {
		int r1 = std::max(-size, -q - size);
		int r2 = std::min(size, -q + size);

		handleSpacesWhileDrawing();

		for (int r = r1; r <= r2; r++) {
			auto hex = map.find(Hex(q, r, -q - r));

			if (hex != map.end()) {
				/*if (!hex->isOccupied) {
					std::cout << "_";
				}
				else if (hex->isWhite) {
					std::cout << "W";
				}
				else {
					std::cout << "B";
				}*/
				std::cerr << "(" << hex->q << "," << hex->r << "," << hex->s << ")";

				std::cerr << " ";
			}
			else if (r != r1) {
				std::cerr << "  ";
			}
		}

		std::cerr << "\n";
	}
}


void Board::printChain(const std::vector<Hex>& chain) {
	std::cerr << "Chain:\n";

	for (const auto& hex : chain) {
		std::cerr << hex.q << " " << hex.r << " " << hex.s << "\n";
	}
	std::cerr << "\n";
}


void Board::handleSpacesWhileDrawing() {
	for (int i = 0; i < spacesQuantity; i++) {
		std::cout << " ";
	}

	if (spacesQuantity == 0) {
		hasPassedMiddleLine = true;
	}

	if (!hasPassedMiddleLine) {
		spacesQuantity--;
	}
	else {
		spacesQuantity++;
	}
}


std::string hexToString(const Hex& hex) {
	return std::to_string(hex.q) + ',' + std::to_string(hex.r) + ',' + std::to_string(hex.s);
}


std::string chainToString(const std::vector<Hex>& chain) {
	std::vector<std::string> stringChain;
	for (const auto& hex : chain) {
		stringChain.push_back(hexToString(hex));
	}
	std::sort(stringChain.begin(), stringChain.end());
	std::string chainString;
	for (const auto& hexString : stringChain) {
		chainString += hexString + ';';
	}
	return chainString;
}


void Board::countChains() {
	// go from left to right in every line
	for (int q = -size; q <= size; q++) {
		int r1 = std::max(-size, -q - size);
		int r2 = std::min(size, -q + size);

		std::vector<Hex> chain;
		for (int r = r1; r <= r2; r++) {
			auto hex = map.find(Hex(q, r, -q - r));
			if (hex != map.end() && hex->isOccupied) {
				chain.push_back(*hex);
			}
			else {
				if (chain.size() >= piecesInLineToTriggerCapture) {
					foundChainsQuantity++;
					for (auto& chainHex : chain) {
						chainHex.countedInChain = true;
					}
				}
				chain.clear();
			}
		}
		
		if (chain.size() >= piecesInLineToTriggerCapture) {
			foundChainsQuantity++;
			for (auto& chainHex : chain) {
				chainHex.countedInChain = true;
			}
		}
		chain.clear();
	}

	// go from top left to bottom right in every line
	for (int r = -size; r <= size; r++) {
		int q1 = std::max(-size, -r - size);
		int q2 = std::min(size, -r + size);

		std::vector<Hex> chain;
		for (int q = q1; q <= q2; q++) {
			auto hex = map.find(Hex(q, r, -q - r));
			if (hex != map.end() && hex->isOccupied) {
				chain.push_back(*hex);
			}
			else {
				if (chain.size() >= piecesInLineToTriggerCapture) {
					foundChainsQuantity++;
					for (auto& chainHex : chain) {
						chainHex.countedInChain = true;
					}
				}
				chain.clear();
			}
		}

		if (chain.size() >= piecesInLineToTriggerCapture) {
			foundChainsQuantity++;
			for (auto& chainHex : chain) {
				chainHex.countedInChain = true;
			}
		}
		chain.clear();
	}


	// go from top right to bottom left in every line
	for (int s = -size; s <= size; s++) {
		int r1 = std::max(-size, -s - size);
		int r2 = std::min(size, -s + size);

		std::vector<Hex> chain;
		for (int r = r1; r <= r2; r++) {
			auto hex = map.find(Hex(-s - r, r, s));
			if (hex != map.end() && hex->isOccupied) {
				chain.push_back(*hex);
			}
			else {
				if (chain.size() >= piecesInLineToTriggerCapture) {
					foundChainsQuantity++;
					for (auto& chainHex : chain) {
						chainHex.countedInChain = true;
					}
				}
				chain.clear();
			}
		}

		if (chain.size() >= piecesInLineToTriggerCapture) {
			foundChainsQuantity++;
			for (auto& chainHex : chain) {
				chainHex.countedInChain = true;
			}
		}
		chain.clear();
	}
}


int Board::getTotalEmptyPlaces() const {
	return totalEmptyPlaces;
}


int Board::getWhitePiecesPlaced() const {
	return whitePiecesPlaced;
}


int Board::getBlackPiecesPlaced() const {
	return blackPiecesPlaced;
}


bool Board::getIsCorrupted() const {
	return isCorrupted;
}


int Board::getFoundChainsQuantity() const {
	return foundChainsQuantity;
}


void Board::setIsCorrupted(bool isCorrupted) {
	this->isCorrupted = isCorrupted;
}


void Board::testBoardPopulation() {
	size--;

	for (int q = -size; q <= size; q++) {
		int r1 = std::max(-size, -q - size);
		int r2 = std::min(size, -q + size);

		for (int r = r1; r <= r2; r++) {
			map.insert(Hex(q, r, -q - r));
		}
	}

	size++;
}
