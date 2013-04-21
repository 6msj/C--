#include <cstdlib>
#include <iostream>
using namespace std;

int fib(long n);
int IsPrime( long number);

int main () {

    int n = 6;
    long X = 0;

    if (IsPrime(317811)) {
        cout << "prime" << endl;
    }
    while(!IsPrime( X ) || !(X > 227000)) {
        cout << "this is n " << n << endl;
        if (IsPrime( X = fib(n) ) && X > 227000) {
            cout << X << endl;
            break;
        }
        n++;
    }

    return 0;

}

int fib(long n) {
    if ( n == 0 || n == 1) {
        return n;
    } else {
        return fib(n-1) + fib(n-2);
    }
}

int IsPrime( long number) {
    if (number <= 1) return 0; // zero and one are not prime
    unsigned int i;
    for (i=2; i*i<=number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}
