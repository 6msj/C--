/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "random.h"
using namespace std;

int main() {
	int headCounter = 0; /* Counts how many times heads shows up. */
	int loopCounter = 0; /* Counts how many times a coin is flipped. */
	while(headCounter != 3) {
		int rand = randomInteger(0,1);
		if(rand == true) {
			headCounter++;
		} else {
			headCounter = 0;
		}
		cout << (rand<1 ? "Tails\n" : "Heads\n");
		loopCounter ++;
	}
	cout << "The number of flips is " << loopCounter << "." << endl;
	system("pause");
    return 0;
}
