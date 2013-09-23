/* Enter a number and see if a subset of the set can sum into that number. */
#include <iostream>
#include <vector>
using namespace std;

void enterNumber(int& testNumber);
void buildVector(vector<int>& set);
bool CanMakeSum(vector<int> set, int targetSum);
void printArray(vector<int> set);
vector<int> MakeNewVector(vector<int> numbers);



int main() {
    vector<int> set;
    int testNumber = 0;
    buildVector(set);
    while(true) {
        enterNumber(testNumber);
        if (CanMakeSum(set, testNumber)) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    }
    return 0;
}

void enterNumber(int& testNumber) {
    cout << "Enter a number > ";
    cin >> testNumber;
}

void buildVector(vector<int>& set) {
    for(int i=0; i<10; i++) {
        set.push_back(i+1);
    }
}

bool CanMakeSum(vector<int> set, int targetSum) {
    if(set.size() == 1) {
        return false;
    }
    if(set[0] + set[1] == targetSum) {
        return true;
    } else {
        vector<int> copy;
        copy = MakeNewVector(set);

        set.erase(set.begin() + 1);
        copy.erase(copy.begin());

        if(CanMakeSum(set, targetSum) || CanMakeSum(copy, targetSum)) {
            return true;
        }
    }
    return false;
}

void printArray(vector<int> set) {
    for(int i=0; i<set.size(); i++) {
        cout << set[i] << endl;
    }
}

vector<int> MakeNewVector(vector<int> numbers) {
    vector<int> copy;
    for(int i=0; i<numbers.size(); i++) {
        copy.push_back(numbers[i]);
    }
    return copy;
}
