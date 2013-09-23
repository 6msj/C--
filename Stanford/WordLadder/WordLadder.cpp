/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [James Nguyen]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

const int ALPHABET = 26;
const int ASCII = 97;

void m_AskWords(string& _startWord_, string& _endWord_, Vector<string>& Ladders);
void m_CheckWords(string& _startWord_, string& _endWord_);
void m_PrintLadder(Vector<string>& Ladder);
void m_CheckOneLetterApart(Vector<string>& Ladder, Lexicon& Lexicon, Queue<Vector<string> >& HoldLadders, Vector<string>& Repeat);
Vector<string> m_MakeNewLadder(Vector<string>& Ladder, string& _word_, Vector<string>& Repeat);

int main() {
    string _startWord_, _endWord_;
    Vector<string> Ladders;
    Vector<string> Repeat; /* Holds words already used. */
    m_AskWords(_startWord_, _endWord_, Ladders);
    m_CheckWords(_startWord_, _endWord_);
    Lexicon _Lexicon_ ("EnglishWords.dat");
    Queue<Vector<string> > HoldLadders;  /* Create an empty queue. */
    HoldLadders.enqueue(Ladders); /* Add the start word to the end of the queue. */
    while(!HoldLadders.isEmpty()) { 
        /* While the queue is not empty. */
        Vector<string> __TestLadder = HoldLadders.dequeue();
        /* If the end of the ladder is equal to the end word, the ladder is found. */
        if(__TestLadder[__TestLadder.size()-1] == _endWord_) {
            cout << "Ladder found. " << endl;
            m_PrintLadder(__TestLadder);
            break;
        }
        m_CheckOneLetterApart(__TestLadder, _Lexicon_, HoldLadders, Repeat);
    }
    cout << "Program ends. " << endl;
    return 0;
}

void m_AskWords(string& _startWord_, string& _endWord_, Vector<string>& Ladders) {
    cout << "What is the start word > ";
    getline(cin, _startWord_);
    cout << "what is the end word > ";
    getline(cin, _endWord_);
    Ladders.push_back(_startWord_);
}

void m_CheckWords(string& _startWord_, string& _endWord_) {
    if(_startWord_.size() != _endWord_.size()) {
        cout << "Words aren't the same length." << endl;
        exit (1);
    }
}

void m_PrintLadder(Vector<string>& Ladder) {
    for(int i=0; i<Ladder.size(); i++) {
        cout << Ladder[i] << " ";
    }
}

void m_CheckOneLetterApart(Vector<string>& Ladder, Lexicon& Lexicon, Queue<Vector<string> >& HoldLadders, Vector<string>& Repeat) {
    /* For every character in the word, for every letter in the alphabet */
    for(int i=0; i<Ladder[Ladder.size()-1].size(); i++) {
        for(int j=0; j<ALPHABET; j++) {
            string _word_ = Ladder[Ladder.size()-1]; /* Use the last word in the vector. */
            _word_[i] = j+ASCII; /* Add the correct ascii number to get characters. */
            if(Lexicon.contains(_word_)) {
                /* Make a copy of current ladder. */
                Vector<string> _newLadder_ = m_MakeNewLadder(Ladder, _word_, Repeat);
                /* If the new vector is empty, don't enqueue it. */
                if(!_newLadder_.isEmpty()) {
                    HoldLadders.enqueue(_newLadder_);
                }
            }
        }
    }
}

Vector<string> m_MakeNewLadder(Vector<string>& Ladder, string& _word_, Vector<string>& Repeat) {
    /* This function creates a new ladder and adds a word to it if there
       isn't that very word already in the ladder. */
    Vector<string> makeNewLadder = Ladder;
    /* Check for repetition. */
    for(int i=0; i<Repeat.size(); i++) {
        if(Repeat[i] == _word_) {
            /* Return an empty vector. */
            makeNewLadder.clear();
            return makeNewLadder;
        }
    }
    /* Add the word to the repeat list and add the word to the new vector. */
    Repeat.push_back(_word_);
    makeNewLadder.push_back(_word_);
    return makeNewLadder;
}
