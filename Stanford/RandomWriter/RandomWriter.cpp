/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [James Nguyen]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
using namespace std;


void getK(ifstream& input, int& orderK);
void buildMap(ifstream& input, Map<string, Vector<char> >& _Map_, int& orderK);
void addToString(ifstream& input, char& ch, string& newKey, Vector<char>& rewindValues, int& orderK);
void addToKey(Map<string, Vector<char> >& _Map_, Vector<char>& associatedValues, string& newKey, ifstream& input);
string findHighest(Map<string, Vector<char> >& _Map_);
void printRandom(string& seedKey, Map<string, Vector<char> >& _Map_);

int main() {
    int orderK;
    ifstream input;
    Map<string, Vector<char> > _Map_;
    getK(input, orderK);
    buildMap(input, _Map_, orderK);
    string seedKey = findHighest(_Map_);
    printRandom(seedKey, _Map_);
	system("pause");
    return 0;
}

void getK(ifstream& input, int& orderK) {
    /* Get the name of the text file the user wants to open
     * and get the the value of Order-K. */
    cout << "What do you want to open? > ";
    string getText;
    getline(cin, getText);
    input.open(getText.c_str());
    cout << "What is K? > ";
    cin >> orderK;
}


void buildMap(ifstream& input, Map<string, Vector<char> >& _Map_, int& orderK) {
    char ch;
    while(input.get(ch)) {
		input.putback(ch);
        Vector<char> associatedValues; /* All the values associated with a key. */
        Vector<char> rewindValues; /* Holds chars to be put back into stream. */
        string newKey = "";

        /* Create a new key by appending as many letters as K value. */
        addToString(input, ch, newKey, rewindValues, orderK);

        /* Add to the key Map. */
        addToKey(_Map_, associatedValues, newKey, input);

        /* Put back the characters into ifstream from reverse. */
        for(int i=orderK-1; i>0; i--) {
            input.putback(rewindValues[i]);
        }
    }

}

void addToString(ifstream& input, char& ch, string& newKey, Vector<char>& rewindValues, int& orderK) {
    for(int i=0; i<orderK; i++) {
		input.get(ch);
        newKey.append(1, ch);
        rewindValues.push_back(ch);
    }
}

void addToKey(Map<string, Vector<char> >& _Map_, Vector<char>& associatedValues, string& newKey, ifstream& input) {
    /* If the map contains the key, add the next char to the vector holding associated values for the key.
     * Else the key is new, so create a new key. */
    char nextChar = input.peek();
    if(_Map_.containsKey(newKey)) {
        _Map_[newKey].push_back(nextChar);
        //cout << "Contains Key " << newKey << endl;
    } else {
        //cout << "Making new Key " << newKey << endl;
        associatedValues.push_back(nextChar);
        _Map_.put(newKey, associatedValues);
    }
}

string findHighest(Map<string, Vector<char> >& _Map_) {
    int initialSize = 1;
    string stringKey = "";
    foreach(string key in _Map_) {
        if(_Map_[key].size() > initialSize) {
            initialSize = _Map_[key].size();
            stringKey = key;
        }
    }
    return stringKey;
}

void printRandom(string& seedKey, Map<string, Vector<char> >& _Map_) {
    int randomInt;
    int charToOutput;
    cout << seedKey;
    cout << "How many characters do you want to output? > ";
    cin >> charToOutput;
    for(int i=0; i<charToOutput; i++) {
        /* If the key isn't the map, end. */
        if(!_Map_.containsKey(seedKey)) {
            break;
        }
        /* Use a random letter from the vector corresponding to that seed. */
        randomInt = randomInteger(0, _Map_[seedKey].size()-1);
        cout << _Map_[seedKey][randomInt];
        seedKey += _Map_[seedKey][randomInt];
        seedKey.erase(0,1);
    }
}
