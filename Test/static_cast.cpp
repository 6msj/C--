#include <iostream>
using namespace std;

int main() {
    int number = 5;
    void *pVoid = &number;
    int *pInt = static_cast<int*>(pVoid);
    cout << *pInt << endl;
    return 0;
}
