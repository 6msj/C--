/*
 * File: BalancingParens.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the balancing parentheses problem on
 * Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

bool isBalanced(string exp);
int findPosition(string exp);

/* Main program */

int main() {
   // [write a test program here]
   if(isBalanced("()[]8{}")) {
       cout << "true" << endl;
   } else {
       cout << "false" << endl;
   }
   return 0;
}

/*
 * Function: isBalanced
 * Usage: if (isBalanced(exp)) . . .
 * ---------------------------------
 * Returns true if the string exp is balanced, which means that it
 * is either (a) empty or (b) contains a consecutive paired operator
 * and the string is balanced if you remove that operator.
 */

bool isBalanced(string exp) {
   // [Fill in this code]
   if(exp == "") {
       return true;
   } else {
       int position = findPosition(exp);
       if(position == -1) return false;
       exp.erase(position, 2);
       return isBalanced(exp);
   }
   return false;
}

int findPosition(string exp) {
    int pos = -1;

    pos = exp.find("()");
    if(pos != -1) {
        return pos;
    }
    pos = exp.find("[]");
    if(pos != -1) {
        return pos;
    }

    pos = exp.find("{}");
    if(pos != -1) {
        return pos;
    }
    
    return -1;
}

