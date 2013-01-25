#include <iostream>
#include <vector>
using namespace std;

void MakeVector(vector<int>& numbers);
void MakeNewVector(vector<int>& copy, vector<int>& numbers);
void printArray(vector<int> set);

int main() {
    vector<int> numbers;
    MakeVector(numbers);
    vector<int> copy(numbers);
    printArray(copy);
    copy.erase(copy.begin());
    //MakeNewVector(copy, numbers);
    //copy.erase(copy.begin() + 1);
    return 0;
}

void printArray(vector<int> set) {
    for(int i=0; i<set.size(); i++) {
        cout << set[i] << endl;
    }
}

void MakeNewVector(vector<int>& copy, vector<int>& numbers) {
    for(int i=0; i<numbers.size(); i++) {
        copy.push_back(numbers[i]);
    }
}

void MakeVector(vector<int>& numbers) {
    for(int i=0; i<10; i++) {
        numbers.push_back(i+1);
    }
}
