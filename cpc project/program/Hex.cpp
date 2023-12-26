#include "Hex.h"


Hex::Hex(int q, int r, int s) :
	q(q),
	r(r),
	s(s) {
	isOccupied = false;
	isWhite = false;
}


Hex::Hex(int q, int r, int s, bool isOccupied, bool isWhite) :
	q(q),
	r(r),
	s(s),
	isOccupied(isOccupied),
	isWhite(isWhite) {
}


void Hex::add(const Hex& other) {
	q += other.q;
	r += other.r;
	s += other.s;
}


Hex Hex::addHexes(Hex hex1, Hex hex2) {
	return Hex(hex1.q + hex2.q, hex1.r + hex2.r, hex1.s + hex2.s);
}


void Hex::subtract(const Hex& other) {
	q -= other.q;
	r -= other.r;
	s -= other.s;
}


void Hex::multiply(int factor) {
	q *= factor;
	r *= factor;
	s *= factor;
}


int Hex::length() const {
	return (abs(q) + abs(r) + abs(s)) / 2;
}


int Hex::distance(const Hex& other) const {
	return (*this - other).length();
}


Hex Hex::directionHex(int direction) const {
	try {
		 return directions[direction];
	 }
	 catch (const std::out_of_range& e) {
		 std::cerr << "Direction out of range";
	 }

	 return Hex(0, 0, 0);
}


Hex Hex::neighbor(int direction) const {
	return *this + directionHex(direction);
}


char Hex::getColor() const {
	if (isOccupied) {
		if (isWhite) {
			return 'W';
		}
		else {
			return 'B';
		}
	}
	else {
		return ' ';
	}
}


bool Hex::operator==(const Hex& other) const {
	return q == other.q && r == other.r && s == other.s;
}


bool Hex::operator!=(const Hex& other) const {
	return !(*this == other);
}


Hex Hex::operator+(const Hex& other) const {
	return Hex(q + other.q, r + other.r, s + other.s);
}


Hex Hex::operator-(const Hex& other) const {
	return Hex(q - other.q, r - other.r, s - other.s);
}

Hex Hex::operator*(int factor) const {
	return Hex(q * factor, r * factor, s * factor);
}
