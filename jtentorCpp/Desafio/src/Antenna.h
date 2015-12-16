/*
 * Antenna.h
 *
 *  Created on: 24 de nov. de 2015
 *      Author: jtentor
 */

#ifndef ANTENNA_H_
#define ANTENNA_H_

#include <cmath>
#include <bitset>

class Antenna {
public:
	Antenna(const int &x, const int &y, const int &r, const int &limit);
	virtual ~Antenna();

	bool isNear(const Antenna &other);
	bool isNear(const Antenna *other);

public:
	int X;
	int Y;
	int R;
	int Count;
	std::bitset<100> Near;
};

Antenna::Antenna(const int &x = 0, const int &y = 0, const int &r = 0, const int &limit = 1) {
	this->X = x;
	this->Y = y;
	this->R = r;
	this->Count = 0;
	for (int i = 0; i < limit; ++i) {
		this->Near[i] = false;
	}
}

Antenna::~Antenna() {
}

bool Antenna::isNear(const Antenna &other) {
	return (std::sqrt( (this->X - other.X) * (this->X - other.X) + (this->Y - other.Y) * (this->Y - other.Y) ) <= (this->R + other.R));
}

bool Antenna::isNear(const Antenna *other) {
	return (std::sqrt( (this->X - other->X) * (this->X - other->X) + (this->Y - other->Y) * (this->Y - other->Y) ) <= (this->R + other->R));
}

#endif /* ANTENNA_H_ */
