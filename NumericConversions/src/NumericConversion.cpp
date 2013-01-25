/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [James Nguyen]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 */

#include <iostream>
#include <string>
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

void whileIntString();
void whileStringInt();

/* Main program */

int main() {
    whileIntString();
    whileStringInt();
    return 0;
}

int stringToInt(string str) {

    /* Multiply holds the value to multiply num by.
     * If str is 10, the 1 needs to be multiplied by 10 when adding. 
     * num will have to be increasingly multiplied by 10 if the number
     * has more digits, so multiply it as many times as the length
     * of the string. */
    

	int multiply = 1;
	for(int i=0; i<str.length()-1; i++) {
		multiply *= 10;
	}

    /* If the first char in the string is equal to 45,
     * it means the char is a '-', which means the number is negative. 
     * Return the whatever it evaluates to to be negative. */

    if(str[0] == 45) {
        return (-1 * (stringToInt(str.substr(1,str.length()-1))));
    }

    /* Base case is when there is only one char left to evaluate,
     * in that case, return the letter and stop the recursion. */

	if(str.length() == 1) {
		int num = str[0] - 48;
		return num;
	} else {
		int num = str[0] - 48;
		return (num*multiply + stringToInt(str.substr(1,str.length()-1)));
	}

}

string intToString(int n) {

    /* If n is negative, change it to positive and prepend the '-' character. */

    if(n < 0) {
        n += -(n+n);
        return (string() = '-' + intToString(n));
    }

    /* If n % 10 = n, n is a single digit, so return that single digit as a string.
     * Otherwise, run the function again by extracting the last digit using modulus
     * extracting the front using division by ten. */

    if(n % 10 == n) {
        char letter = n + '0';
        return (string() + letter);
    } else {
        return (intToString(n/10) + intToString(n%10));
    }
}

void whileIntString() {
    int num;
    for(int i=0; i<10; i++) {
        cout << "Enter a letter to convert to a string. ";
        cin >> num;
        cout << "This is a string: " << intToString(num) << endl;
    }
}


void whileStringInt() {
    string num;
    for(int i=0; i<10; i++) {
        cout << "Enter a string to convert to a number. ";
        cin >> num;
        cout << "This is a int: " << stringToInt(num) << endl;
    }
}
