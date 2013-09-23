#include <iostream>
using namespace std;

/* Takes a number and prints it in Binary. */

void PrintInBinary(int number);

int main() {
    int number = 8;
    PrintInBinary(number);
    return 0;
}

void PrintInBinary(int number) {
    if(number == 0 || number == 1) {
        cout << number;
    } else {
        PrintInBinary(number/2);
        cout << number%2;
    }
}
