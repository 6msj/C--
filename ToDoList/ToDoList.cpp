#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

/*Void Functions*/

/*checks the todo list to see if there's one, if there isn't it'll make one */
void checkForToDo(ifstream& in, ofstream& createList, vector<string>& toDo);

/*function to create the todo list if there isn't one */
void createToDoList(ofstream& createList, ifstream& in, vector<string>& toDo);

/*outputs what's in the todo.txt file, whether it was just created or opened */
void outputTodoList(ifstream& in, ofstream& createList, int& keepCount, vector<string>& toDo);

/*allows user a choice to remove or add tasks, calls addATask or removeATask */
void userChoiceAddRemove(ifstream& in, ofstream& createList, int& keepCount, vector<string>& toDo);

/* adds tasks, user can keep doing it until they want to stop */
void addATask(vector<string>& toDo, int& keepCount);

/* removes tasks, user can keep doing it until they want to stop */
void removeATask(vector<string>& toDo, int& keepCount);

/* prints the final todo list, after remove/add options are done */
void finalToDoList(vector<string>& toDo, int& keepCount, int& howManyTimesThisThingLoops);

/* rewrites the todo.txt by outputting a new one */
void rewriteInputOutputFile(ifstream& in, ofstream& createList, vector<string>& toDo);

/*Returning Values*/

bool checkUserChoice(char a);

/*checks for empty spaces in the array and if so, moves them to the end */
vector<string> rearrangeToDo(vector<string>& toDo, int placeholder);

int main() {
    ifstream in;
    ifstream sample;
    ofstream createList;
    vector<string> toDo; //will be used later for printing out the todo list
    int keepCount = 0;     //used as a counter for for loop later on
    checkForToDo(in, createList, toDo); //checks if there's a txt file, if yes, proceed, otherwise make one
    outputTodoList(in, createList, keepCount, toDo); //prints out the current txt file named "toDo.txt"
    userChoiceAddRemove(in, createList, keepCount, toDo); //gives the option to remove or add a new item
    rewriteInputOutputFile(in, createList, toDo); //rewrites the to do list in memory to "toDo.txt"
    return 0;
}

void checkForToDo(ifstream& in, ofstream& createList, vector<string>& toDo) {
    in.open("toDo.txt");
    if(in) {
        cout << "To Do list opened." << endl;
    } 
    else if(!(in)) {
        cout << "No To Do List found." << endl;
        cout << "Do you want to create a new list? (y/n) ";
        char userchoice;
        cin >> userchoice;
        if(checkUserChoice(userchoice)) {
            cout << "New To Do List!" << endl;
            createToDoList(createList, in, toDo); //function to create a todo list if one isn't found
        } 
        else { 
            cout << "Good bye." << endl;
            exit (0);
        }
    }
}

void createToDoList(ofstream& createList, ifstream& in, vector<string>& toDo) {
    createList.open("toDo.txt"); 
    if(createList.is_open()) {
        cout << "File toDo.txt has been created." << endl;
        cout << "How many tasks do you have?" << endl;
        int firstRunNumberofTasks;
        cin >> firstRunNumberofTasks; //if file isn't created, asks for how many tasks there is.
        cin.ignore(1024, '\n'); //ignores the extra space at the end of cin so getline doesn't error out
        for(int i=0; i<firstRunNumberofTasks; i++) {
            string placeholder = "";
            cout << "Enter Task: ";
            getline(cin, placeholder);
            cout << "You said you were going to " << placeholder << endl; //check
            createList << placeholder << endl; //outputs user's choice to the ofstream opened file
        }
        cout << "To Do list created, checking for errors..." << endl;
        createList.close(); //closes the list to be opend again later
        checkForToDo(in, createList, toDo); //runs the previous function again
    } else {
        cout << "Can't open file for some reason!" << endl; //unneeded check..probably
    }
}

void outputTodoList(ifstream& in, ofstream& createList, int& keepCount, vector<string>& toDo) {
    /*Test: Is the file still opened?*/
    string line;
    while(!in.eof()) { 
       getline(in, line); //gets a line from toDo.txt
       //cout << "Task " << keepCount << ": " << line << endl;
       if(line == "") { 
           break;  //There's an empty white line at the end of the file that shouldn't be read
       }
       toDo.push_back(line); //adding to the vector 
       keepCount ++; //keeps a running tally of how many times the file outputs, needed later when rewriting the todo list
    }
    for(int i=0; i<keepCount; i++) {
        cout << "Task " << i+1 << ": " <<  toDo[i] << endl; //outputs what's in toDo
    }
}

void userChoiceAddRemove(ifstream& in, ofstream& createList, int& keepCount, vector<string>& toDo) { 
    in.open("toDo.txt");
    //if(!in) {
    //    cout << "No To Do List found. Exiting. " << endl;
    //    return;
    //}
    cout << "You have a choice of [a]dding or [r]emoving a task." << endl;
    char userChoice;
    cin >> userChoice;
    if(userChoice == 'a') {
        addATask(toDo, keepCount); //goes to function addATask
    } 
    else if(userChoice == 'r') {
        removeATask(toDo, keepCount); //goes to function removeATask
    } else {
        cout << "You didn't add or remove anything." << endl;       
    }
}

void addATask(vector<string>& toDo, int& keepCount) {
    int howManyTimesThisThingLoops = 0;
    cin.ignore(1024, '\n');
    while(true) {
        cout << "What do you want to add? ";
        string addWhat;
        getline(cin, addWhat);
        //cout << "You said you were going to " << addWhat << endl; //check
        cout << "Is that all? (y/n) "; 
        howManyTimesThisThingLoops ++; //keeps track of the amount of times the while loops through, will be used for the final total of todo list
        toDo.push_back(addWhat); //adds user input and pushes it to the toDo vector
        char yesNo;
        cin >> yesNo;
        cin.ignore(1024, '\n');
        if(yesNo == 'n') {
            cout << "You've chose to add another task." << endl;
        } else {
            cout << "You either entered y, or another letter." << endl;
            //cout << "howManyTimesThisThingLoops" << howManyTimesThisThingLoops << endl; //check
            //cout << "keepCount" << keepCount << endl; //check
            //cout << keepCount + howManyTimesThisThingLoops << endl; //a check to see if keepCount and howManyTimesThisThingLoops are correct
            finalToDoList(toDo, keepCount, howManyTimesThisThingLoops); //prints the resulting to do list
            break;
        }
    }
}

void removeATask(vector<string>& toDo, int& keepCount) {
    int howManyTimesThisThingLoops = 0;
    int choiceOfDeletion;
    char userChoice;
    while(true) {
        cout << "What do you want to delete? : ";
        cin >> choiceOfDeletion;
        for(int i=0; i<keepCount; i++) { //less than the amount of times it looped before when originally outputting the todo list
            if(choiceOfDeletion == i+1) { //+1 corresponds to the number they inputted +1 to the index, so the numbers match up with the item on the list
                toDo[i] = ""; //if choiceOfDeletion equals whatever task, that task becomes whitespace
            }
        }
        cout << "You removed Task " << choiceOfDeletion << "." << endl;
        howManyTimesThisThingLoops --; //when removing a task, one has to cut the counter by one for later when rewriting the todo list
        cout << "Do you want to continue removing tasks? : ";
        cin >> userChoice;
        if(!(checkUserChoice(userChoice))) {
            break;
        }
    }
    toDo = rearrangeToDo(toDo, keepCount); //function to rearrange the todo list properly
    finalToDoList(toDo, keepCount, howManyTimesThisThingLoops); //prints out the final list
}

void finalToDoList(vector<string>& toDo, int& keepCount, int& howManyTimesThisThingLoops) {
    cout << "Final Task List" << endl;
    for(int i=0; i<keepCount+howManyTimesThisThingLoops; i++) { //takes both values keepCount and howManyTimesThisThingLoops 
        cout << "Task " << i+1 << ": " << toDo[i] << endl; //and adds them, total should be how many times the list loops
    }
}

void rewriteInputOutputFile(ifstream& in, ofstream& createList, vector<string>& toDo) {
    createList.open("toDo.txt");
    for(int i=0; i<toDo.size(); i++) {
        createList << toDo[i] << endl; //rewrites the new toDo.txt based on the vector toDo
    }
    cout << "Finished. " << endl;
}

vector<string> rearrangeToDo(vector<string>& blah, int placeholder) {
    for(int i=0; i<placeholder-1; i++) { //checks for "" has to be -1 or else it segfaults
        if(blah[i] == "") {             
            blah[i] = blah[i+1]; //if there's "", it changes it with the next string
            blah[i+1] = "";
        }
    }
    /*check
    for(int i=0; i<placeholder; i++) { //checks what the resulting vector looks like
        cout << blah[i] << endl;
    } */
    return blah;
}

bool checkUserChoice(char a) { //returns true if the user says [y]es, otherwise will return false
    if(a == 'y') {
        return true;
    } else {
        return false;
    }
}


