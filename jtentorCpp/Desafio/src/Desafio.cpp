//============================================================================
// Name        : Desafio.cpp
// Author      : Julio Tentor
// Version     :
// Copyright   : Creative Commons
// Description : Problema A - AM/FM
//============================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

#include "Antenna.h"

void doTest();
void doHelp();

/**
 * Esto es para tener opciones en la línea de comandos de manera
 * que se puea estudiar el comportamiento del algoritmo
 */
static int verboseFlag = 0;
static int showTimeFlag = 0;

static struct option getoptData[] = {
		{"verbose", 0, &verboseFlag, 1},
		{"time", 0, &showTimeFlag, 1},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0}
};


/**
 * Main program
 */

int main(int argc, char **argv) {

	clock_t clockStart, clockFinal;
	clockStart = clock();

	int getoptCase;
	int getoptIndex = 0;
	while ((getoptCase = getopt_long(argc, argv, "vth", getoptData, &getoptIndex)) != -1)  {
		switch (getoptCase) {
		case 0:
			break;

		case 'v':
			verboseFlag = true;
			break;

		case 't':
			showTimeFlag = true;
			break;

		case 'h':
			doHelp();
			exit(0);
		case '?':
			doHelp();
			exit(-1);
		}
	}
	// Call algorithm that solves the problem
	doTest();

	clockFinal = clock();

	if (verboseFlag || showTimeFlag) {
		float timeElapsed = (clockFinal - clockStart) / (float) CLOCKS_PER_SEC;
		std::cout << "Time elapsed = " << timeElapsed << " [" << clockFinal << " - " << clockStart << "]" << std::endl;
	}

	return 0;
}

/**
 * Show help
 */
void doHelp() {
	std::cout << "Options:" << std::endl;
	std::cout << "  -t --time show time elapsed" << std::endl;
	std::cout << "  -v --verbose show more information" << std::endl;
}

/**
 * Resolving the problem
 */
void doTest() {

	/**
	 * Read number of antennas
	 */
	int limit;
	std::cin >> limit;

	std::vector<Antenna *> antennas;
	antennas.reserve(limit);

	/**
	 * Read data from stdin -> O(N)
	 */
	int x,y,r;
	for(register int i = 0; i < limit; ++i) {
		std::cin >> x;
		std::cin >> y;
		std::cin >> r;
		antennas.push_back(new Antenna(x, y, r, limit));
	}

	/**
	 * Determines nearness for circles pairs -> O(N^2)
	 */
	Antenna *current, *testing;
	for(register int i = 0; i < limit; ++i) {
		current = antennas[i];

		(current->Count)++;
		current->Near[i] = true;

		for (register unsigned int j = i + 1; j < antennas.size(); ++j) {
			testing = antennas[j];
			if (current->isNear(testing)) {
				(current->Count)++;
				current->Near[j] = true;
				(testing->Count)++;
				testing->Near[i] = true;
			}
		}
	}

	/**
	 * Check circles pairs to have common points -> O(N^3)
	 */
	std::bitset<100> test;

	int maxCount = -1, maxPosition = -1;
	for (register int i = 0; i < limit; ++i) {
		current = antennas[i];
		// get a working copy of nearness pair of circles
		for (register int j = 0; j < limit; ++j) {
			test[j] = current->Near[j];
		}
		for (register int j = 0; j < limit; ++j) {
			if ((i != j) && test[j]) { // if not the same and is near
				testing = antennas[j];
				for (register int k = 0; k < limit; ++k) {
					if (test[k]) {
						if (!(testing->Near[k])) { // if is in current and not in b
							test[k] = false;
							(current->Count)--;
						}
					}
				}
			}
		}
		/// remember the max count and position
		if (current->Count > maxCount) {
			maxCount = current->Count;
			maxPosition = i;
		}
	}

	if (!verboseFlag) {
		std::cout << maxCount << std::endl;
	} else { // if verbose option show more info
		std::cout << maxCount << " antenas comunes ";
		for (int j = 0; j < limit; ++j) {
			if (antennas[maxPosition]->Near[j]) {
				std::cout << std::setw(3) << j;
			}
		}
		std::cout << std::endl;

		for(int i = 0; i < limit; ++i) {
			std::cout << std::setw(2) << i << " [" << std::setw(2) << antennas[i]->X << ", " << std::setw(2) << antennas[i]->Y << ", "  << std::setw(2) << antennas[i]->R << "]";
			std::cout << " : " << std::setw(2) << antennas[i]->Count << " - ";
			for (int j = 0; j < limit; ++j) {
				std::cout << " " << (antennas[i]->Near[j] ? '*' : ' ');
			}
			std::cout << std::endl;
		}
	}
}

