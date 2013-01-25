#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

enum Type {
    INT,
    FLOAT,
};

void Print(void *pValue, Type eType) {
    switch(eType) {
        case INT:
            cout << *static_cast<int*>(pValue) << endl;
            break;
        case FLOAT:
            cout << *static_cast<float*>(pValue) << endl;
            break;
    }
}

int main() {
    int nValue = 5;
    float fValue = 7.5;
    Print(&nValue, INT);
    Print(&fValue, FLOAT);
    return 0;

}
