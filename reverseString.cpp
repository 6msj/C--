#include <iostream>
#include <string>
using namespace std;

void reverseString(char word[]);

int main() {
    char word[] = "String";
    reverseString(word);
    return 0;
}


void reverseString(char word[]) {
    for(int i=0, j=5; i<=j; i++, j--) {
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
    printf("%s", word);

}
