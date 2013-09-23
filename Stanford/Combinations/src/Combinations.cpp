/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [James Nguyen]
 * This file is the starter project for the recursive combinations problem.
 */

#include <iostream>
#include "simpio.h"
using namespace std;

int pascal(int n, int k);

int main() {
    bool running = true;
    while(running) {
        int row, column;
        cout << "Row? ";
        cin >> row;
        cout << "Column? ";
        cin >> column;
        int num = pascal(row,column);
        cout << "The pascal's triangle number for that column and location is " << num << "." << endl;
        if(row < 0 || column < 0) {
            running = false;
        }
    }
        return 0;
}

int pascal(int n, int k) {

    /* Base: The First Row, which starts at 1. */
    if(n <= 0 && k <= 0) {
        return 1;
    }

    /* This would be on the end of the pascal's triangle,
     * so k needs to decremented, otherwise the loop will
     * run incorrectly and forever. */
    if(k == n) {
        return (pascal(n-1, k-1));
    }

    /* This would be at the beginning of the pascal's triangle,
     * so k should not be changed. */
    if(k == 0) {
        return (pascal(n-1, k));
    }

    /* Otherwise, the number wanted is the sum
     * of the two above numbers, which is: 
     * one row up left column, one row up and same column. */
    return (pascal(n-1,k-1) + (pascal(n-1,k)));
}
