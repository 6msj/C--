#include <iostream>
using namespace std;


int CountWays(int numStairs);



int main() {
    int numStairs = 4;
    int steps;
    steps = CountWays(numStairs);
    cout << steps << endl;
    return 0;
}


int CountWays(int numStairs) {
    if(numStairs <= 1) {
        return 1;
    } else {
        return(CountWays(numStairs-1) + CountWays(numStairs-2));
    }

}
