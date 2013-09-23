#include <iostream>
#include <vector>
using namespace std;


/* Subset Sum Problem */

void CreateVector(vector<int> & numbers);
void Encapsulate(vector<int> numbers, int targetSum, int &counter);
bool CanMakeSum(vector<int> & nums, int targetSum);

int main() {
	vector<int> numbers;
	int targetSum = 0;
    int counter = 0;
	CreateVector(numbers);
    for (int i=1; i<numbers.size(); i++) {
        Encapsulate(numbers, numbers[numbers.size()-i], counter);
        //cout << "target num: " << numbers[numbers.size()-i] << endl;
        cout << counter << endl;
    }
    cout << "true" << endl;
    cout << counter << endl;
    /*
     *while(numbers.size()) {
     *    Encapsulate(numbers, numbers[numbers.size()-1]);
     *}
     */
	return 0;
}

void CreateVector(vector<int> & numbers) {
	numbers.push_back(3);
	numbers.push_back(4);
	numbers.push_back(9);
	numbers.push_back(14);
	numbers.push_back(15);
    numbers.push_back(19);
    numbers.push_back(28);
    numbers.push_back(37);
    numbers.push_back(47);
    numbers.push_back(50);
    numbers.push_back(54);
    numbers.push_back(56);
    numbers.push_back(59);
    numbers.push_back(61);
    numbers.push_back(70);
    numbers.push_back(73);
    numbers.push_back(78);
    numbers.push_back(81);
    numbers.push_back(92);
    numbers.push_back(95);
    numbers.push_back(97);
    numbers.push_back(99);
}

void Encapsulate(vector<int> numbers, int targetSum, int &counter) {
	for(int i=0; i<numbers.size(); i++) {
		int subNumber = numbers[0];
        if( targetSum - subNumber > 0 || targetSum - subNumber == 0) {
		    targetSum = targetSum - subNumber;
            if(targetSum == 0) {
                break;
            }
        } else {
            break;
        }
		numbers.erase(numbers.begin() + 0);
		vector<int> numbers_copy = numbers;
        cout << "target sum : " << targetSum << endl;
        if (CanMakeSum(numbers_copy, targetSum)) {
            counter++;
            continue;
        }
        targetSum = targetSum + subNumber;
        numbers.push_back(subNumber);
	}
}

bool CanMakeSum(vector<int> & nums, int targetSum) {
	if(targetSum == 0)
		return true;
	if(nums.empty())
		return false;
	targetSum = targetSum - nums[0];
	nums.erase(nums.begin() + 0);
	return CanMakeSum(nums, targetSum);
}
