/*
 * File: Obenglobish.cpp
 * ----------------------
 * Name: [James Nguyen]
 * This file is the starter project for the Obenglobish problem.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* The string to put in, if a vowel is found. */
const string OB = "ob";

string obenglobish(string word);
bool checkVowel(char letter);
void checkRepeat(string& word, int& index, string& newWord);

/* Main program */

int main() {
    while (true) {
        string word = getLine("Enter a word: ");
        if (word == "") break;
        string trans = obenglobish(word);
        cout << word << " -> " << trans << endl;
    }
    return 0;
}

string obenglobish(string word) {
    string newWord = ""; /* This word will be returned. */
    int index = 0;
    while(index < word.length()) {

        /* If the index is at the end of the string, and the letter there is an 'e',
         * add 'e' to the newWord and end the loop. */
        if(index == word.length()-1 && word[index] == 'e') {
            newWord += word[index];
            break;
        }

        if(checkVowel(word[index])) {
            /* If the current letter is a vowel, add the corresponding letters to the new word.
             * Then check the next char to see if it is a vowel or not.
             * Check the next char by adding one to the index.
             * */
            newWord += OB;
            newWord += word[index];
            checkRepeat(word, index, newWord);
        } else {
            /* If the current letter is not a vowel, 
             * simply add the current letter to the new word. */
            newWord += word[index];
        }
        index++;
    }
    return newWord;
}

bool checkVowel(char letter) {
    /* Is given a letter to evaluate, if it's a vowel,
     * it returns true. */
    switch(letter) {
        case 'a': return true; break;
        case 'e': return true; break;
        case 'i': return true; break;
        case 'o': return true; break;
        case 'u': return true; break;
        default: return false;
    }
}

void checkRepeat(string& word, int& index, string& newWord) {
    /* While the current letter is a vowel, check the next one. */
    while(checkVowel(word[index+1])) {
        newWord += word[index+1];
        index++;
    }
}
