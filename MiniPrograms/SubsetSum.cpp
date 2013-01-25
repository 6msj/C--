#include <iostream>
using namespace std;

void RecSubsets(string soFar, string rest);
void ListSubsets(string sr);

int main() {
    string test = "test";
    ListSubsets(test);
    return 0;
}

void RecSubsets(string soFar, string rest) {
    if (rest == "") {
        cout << soFar << endl;
    } else {
        // add to subset, remove from rest, recur
        RecSubsets(soFar + rest[0], rest.substr(1));
        // don't add to subset, remove from rest, recur
        RecSubsets(soFar, rest.substr(1));
    }

}

void ListSubsets(string str) {
    RecSubsets("", str);

}
