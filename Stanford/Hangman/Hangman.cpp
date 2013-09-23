#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <ctime> 
#include <cstdlib> 
#include <ctype.h>
using namespace std; 

/*Returning Values*/
string returnRandom(int n); /*returns a word*/
bool checkLetters(string& underScores, char& userEnterLetter, string& hangmanWord);

/*Void Functions*/
void assignValues(string& underScores, string& hangmanWord);
void compareValues(string& underScores, string& hangmanWord, int& counter, int& numGueses);
void instructions();

int main () {
    instructions();
    unsigned seed = time(0);
    string underScores;
    srand(seed);
    int x = 1 + rand() % 10;
    //cout << returnRandom(x);
    string hangmanWord = returnRandom(x);
    int counter = 1;
    assignValues(underScores, hangmanWord);
    int numGuesses = 8;
    while(!(underScores == hangmanWord || numGuesses==0)) {
        compareValues(underScores, hangmanWord, counter, numGuesses);
        if(underScores == hangmanWord) {
            cout << "You won!" << endl;
        }
        if(numGuesses==0) {
            cout << "You lost.." << endl;
        }
    }
    return 0;
}

void instructions() {
    cout << "Welcome to the Hangman game." << endl;
    cout << "You have eight guesses to find out the word." << endl;
    cout << "If you get it wrong, you lose a guess, if you get it right, nothing happens." << endl;
}

string returnRandom(int n) {
    string wordToReturn;
    switch(n) {
        case 1: wordToReturn = "WORD"; break;
        case 2: wordToReturn = "PHONE"; break;
        case 3: wordToReturn = "MOUSE"; break;
        case 4: wordToReturn = "DRAGON"; break;
        case 5: wordToReturn = "WATER"; break;
        case 6: wordToReturn = "FIRE"; break;
        case 7: wordToReturn = "FOREST"; break;
        case 8: wordToReturn = "MOUNTAIN"; break;
        case 9: wordToReturn = "LIGHT"; break;
        case 10: wordToReturn = "SPOON"; break;
        default: wordToReturn = "NOTHING"; break;
    }
    return wordToReturn;
}

void assignValues(string& underScores, string& hangmanWord) {
    underScores = "-";
    /*check*/
    for(int i=1; i< hangmanWord.size(); i++) {
        underScores += '-';
    }
    /*check*/
    for(int i=0; i<hangmanWord.size(); i++) {
        cout << underScores[i] << " ";
    }
}

void compareValues(string& underScores, string& hangmanWord, int& counter, int& numGuesses) {
    string unalteredLetter;
    char userEnterLetter;
    cout << "Enter a letter :"; 
    cin >> unalteredLetter;
    if(unalteredLetter.size() > 1) {
        cout << "Can't be more than one letter. Enter again." << endl;
        cin >> unalteredLetter;
        while(unalteredLetter.size() > 1) {
            cout << "Can't be more than one letter." << endl;
            cin >> unalteredLetter;
        }
    }
    userEnterLetter = toupper(unalteredLetter[0]);
    cout << userEnterLetter;
    int i=0;
    if(checkLetters(underScores, userEnterLetter, hangmanWord)) {
        cout << "Correct." << endl;
        for(int i=0; i<hangmanWord.size(); i++) {
            if(userEnterLetter == underScores[i]) {
                cout << "Entered already. " << endl;
            }
            if(userEnterLetter == hangmanWord[i]) {
                underScores[i] = userEnterLetter;
            }
        }
    } else if(!(checkLetters(underScores, userEnterLetter, hangmanWord))) {
            cout << "Wrong." << endl;
            numGuesses --;
            counter ++;
                
    }
    for(int i=0; i<hangmanWord.size(); i++) {
        cout << underScores[i];
    }
    cout << "The guess is at " << counter << endl;
    cout << "You have " << numGuesses << " guesses left." << endl;
}

bool checkLetters(string& underScores, char& userEnterLetter, string& hangmanWord) {
    int i=0;
    while(i<hangmanWord.size()) {
        if(hangmanWord[i] == userEnterLetter) {
            return true; break;
        }
        i++;
    }
    return false;
}
