/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: James Nguyen
 * This file is the starter project for the cell phone mind-reading problem on
 * Assignment #3
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "hashmap.h"
using namespace std;

/* Function prototypes */

void buildHashMap(HashMap<string, string>& map);
void listCompletions(string digits, Lexicon & lex);
void checkDigits(string digits, Lexicon & lex, HashMap<string, string> map, string currentString);
void checkLexicon(string indexLetters, Lexicon & lex);
string UpToLow(string str);

/* Main program */

int main() {
   Lexicon english("EnglishWords.dat");
   cout << "Cell phone mind-reading problem" << endl;
   while (true) {
      cout << "Enter a set of digits: ";
      string digits = getLine();
      if (digits == "" || digits == "quit") break;
      cout << "The words beginning with those digits are:" << endl;
      listCompletions(digits, english);
   }
   return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lex);
 * ------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon & lex) {
    HashMap<string, string> map;
    buildHashMap(map);
    checkDigits(digits, lex, map, "");
}

/*
 * Function: buildHashMap
 * Usage: buildHashMap(hashmap);
 * -----------------------------
 *  Build a map to sets a digit to the letters on a telephone.
 */

void buildHashMap(HashMap<string, string>& map) {
    map.put("2", "ABC");
    map.put("3", "DEF");
    map.put("4", "GHI");
    map.put("5", "JKL");
    map.put("6", "MNO");
    map.put("7", "PQRS");
    map.put("8", "TUV");
    map.put("9", "WXYZ");
}

/* Function: checkDigits
 * Usage: checkDigits(digits, lexicon, map, currentString);
 * -------------------------------------------------------
 *  Meat of the recursion, the base case is if the string is only one letter. Check it against
 *  the lexicon. Otherwise, chop the string up into separate pieces and add to the currentString.
 */

void checkDigits(string digits, Lexicon & lex, HashMap<string, string> map, string currentString) {
    if(digits.size() == 1) {
        string keyValue = digits.substr(0, 1);
        string indexLetters = map.get(keyValue);
        for(int i=0; i<indexLetters.size(); i++) {
            checkLexicon(currentString + indexLetters.substr(i, 1), lex);
        }
    } else {
        string keyValue = digits.substr(0, 1);
        string indexLetters = map.get(keyValue);
        for(int i=0; i<indexLetters.size(); i++) {
            checkDigits(digits.substr(1), lex, map, currentString + indexLetters.substr(i, 1));
        }
    }
}

/* Function checkLexicon
 * Usage: checkLexicon(letters, lexicon);
 * -------------------------------------
 *  Used in the recursion to check a string to see if it's a
 *  prefix in the lexicon. If a match is found, print it.
 */

void checkLexicon(string indexLetters, Lexicon & lex) {
    string lowerCase = UpToLow(indexLetters);
    foreach (string word in lex) {
        Lexicon newLex;
        newLex.add(word);
        if(newLex.containsPrefix(indexLetters) || newLex.containsPrefix(lowerCase)) {
            cout << word << endl;
        }

    }
}

/* Function UpToLow
 * Usage: UpToLow(string);
 * -----------------------
 *  Change capitals to lower.
 */

string UpToLow(string str) {
    for (int i=0;i<strlen(str.c_str());i++) 
        if (str[i] >= 0x41 && str[i] <= 0x5A) 
            str[i] = str[i] + 0x20;
    return str;
}



