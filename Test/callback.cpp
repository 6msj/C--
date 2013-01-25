#include <iostream>
using namespace std;

void cbfunc();

int main() {
    /* function pointer */
    void (*callback) (void);

    /* point to your callback */
    callback=cbfunc;

    /* perform callback */
    callback();


    return 0;
}

void cbfunc() {
    cout << "called";
}
