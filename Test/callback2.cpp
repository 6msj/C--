#include <iostream>
using namespace std;

int getNum();

int main() {
    int (*callback)() = getNum;
    cout << callback();
    return 0;
}

int getNum() {
    int num;
    cout << "Enter a number!. > ";
    cin >> num;
    return num;
}
