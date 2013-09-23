/*
 * File: BinaryEncoding.cpp
 * ------------------------
 * Starter file for the binary encoding problem on Assignment #3.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

void generateBinaryCode(int nBits);
void generateBinaryWithPrefix(int nBits, string prefix);

/* Main program */

int main() {
   int nBits = getInteger("Number of bits: ");
   generateBinaryCode(nBits);
   return 0;
}

/*
 * Function: generateBinaryCode
 * Usage: generateBinaryCode(nBits);
 * ---------------------------------
 * Lists all the binary values containing the specified number of bits.
 */

void generateBinaryCode(int nBits) {
   // Fill this in
   if(nBits < 0) {
       cout << "Number is less than zero." << endl;
   } else {
       generateBinaryWithPrefix(nBits, "");
   }
}

void generateBinaryWithPrefix(int nBits, string prefix) {
    if(nBits == 0) {
        cout << prefix << endl;
    } else {
        generateBinaryWithPrefix(nBits-1, prefix + "0");
        generateBinaryWithPrefix(nBits-1, prefix + "1");
    }
}
