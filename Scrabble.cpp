#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct typep {
	string name;
	string words;
	int score;
};
/*  welcomes the user and asks them how many players are playing */
void welcome(int& amountOfPlayers);
/*  user enters in their names */
void getNames(vector<typep>& player, int& amountOfPlayers);
/*  function where user enters in their words to be scored */
void userAddsWords(vector<typep>& player, int& amountOfPlayers);
/*  uses the scrabble function and adds each score to the vector holding totals */
void calculateWords(vector<typep>& player, int& amountOfPlayers);
/* prints the score after each player is finished with their words */
void sayTheScore(vector<typep>& player, int& amountOfPlayers);
/*  winner is declared, after using the checkForWinner function */
void declareWinner(vector<typep>& player, int& amountOfPlayers);
/*  function that holds all the value of each character */
void Scrabble(char aa, int& add);
/*  will loop through the function for as long as game continues */
void loop(vector<typep>& player, int& amountOfPlayers);
/*  checks for the winner */
bool checkForWinner(int x, vector<typep>& player, int& amountOfPlayers);

int main() {
	int amountOfPlayers; 
	welcome(amountOfPlayers); /*  determines amount of players playing the game */
	vector<typep> player(amountOfPlayers); 
	getNames(player, amountOfPlayers);
    loop(player, amountOfPlayers);
	declareWinner(player, amountOfPlayers);
	return 0;
}

void welcome(int& amountOfPlayers) {
	cout << "Welcome to the Scrabble Calculator." << endl;
	cout << "How many people are playing?" << endl;
	cin >> amountOfPlayers;
	if(amountOfPlayers>4) {
		cout << "4 is the max for Scrabble. Enter again." << endl;
		cin >> amountOfPlayers;
		while(!(amountOfPlayers<4)) {
			cout << "Enter again." << endl;
			cin >> amountOfPlayers;
		}
	}
}
	
void getNames(vector<typep>& player, int& amountOfPlayers) {
	int x = 1;
	for(int i=0; i<amountOfPlayers; i++) {
		cout << "Player " << x << " ?" << endl;
		string name;
		cin >> name;
		player[i].name = name;
		x += 1;
	}
	cout << "The players are: " << endl;
	for(int i=0; i<amountOfPlayers; i++) {
		cout << player[i].name;
		cout << (i<amountOfPlayers-1 ? ", " : ".") << endl;
	}
}

void userAddsWords(vector<typep>& player, int& amountOfPlayers) {
	cout << endl;
	string input;
	for(int i=0; i<amountOfPlayers; i++) {
		cout << player[i].name << " 's turn." << endl;
		cin >> input;
		player[i].words = input;
	}
	/*check
	for(int i=0; i<amountOfPlayers; i++) {
		cout << player[i].name << player[i].words << endl;
	}*/
}

void calculateWords(vector<typep>& player, int& amountOfPlayers) {
	vector<int> toty(amountOfPlayers);
	for(int i=0; i<amountOfPlayers; i++) {
		toty[i] = 0;
	}
	for(int i=0; i<amountOfPlayers; i++) {
		int totalFromScrabble =0;
		for(int j=0; j<player[i].words.size(); j++) {
			int add =0;
			Scrabble(player[i].words[j], add);
			totalFromScrabble += add;
		}
		toty[i] += totalFromScrabble;
		player[i].score += toty[i];
	}
	/*check */
	for(int i=0; i<amountOfPlayers; i++) {
		cout << player[i].name << " has " << player[i].score; 
		cout << (i<amountOfPlayers-1 ? ", " : ". ");
	}
}

void sayTheScore(vector<typep>& player, int& amountOfPlayers) {
	for(int i=0; i<amountOfPlayers; i++) {
		cout << player[i].name << " has " << player[i].score << ". " << endl;
	}
}

void declareWinner(vector<typep>& player, int& amountOfPlayers) {
	for(int i=0; i<amountOfPlayers; i++) {
		if(checkForWinner(player[i].score, player, amountOfPlayers)) {
			cout << player[i].name << " has won." << endl;
		}
	}
}

void Scrabble(char aa, int& add) {
	switch (aa) {
		case 'e': case 'a': case 'i': case 'o': case 'n':
		case 'r': case 't': case 'l': case 's': case 'u':
			add += 1; break;
		case 'd': case 'g':
			add += 2; break;
		case 'b': case 'c': case 'm': case 'p':
			add += 3; break;
		case 'f': case 'h': case 'v': case 'w': case 'y':
			add += 4; break;
		case 'k':
			add += 5; break;
		case 'j': case 'x':
			add += 8; break;
		case 'q': case 'z':
			add += 10; break;
		case '_': 
			add += 0; break;

		//Capitals
		case 'E': case 'A': case 'I': case 'O': case 'N': case 'R': case 'T': case 'L': case 'S': case 'U':
			add += 2; break;
		case 'D': case 'G':
			add += 4; break;
		case 'B': case 'C': case 'M': case 'P':
			add += 6; break;
		case 'F': case 'H': case 'V': case 'W': case 'Y':
			add += 8; break;
		case 'K':
			add += 10; break;
		case 'J': case 'X':
			add += 16; break;
		case 'Q': case 'Z':
			add += 20; break;
		

	}
}

void loop(vector<typep>& player, int& amountOfPlayers) {
	while(true) {
		userAddsWords(player, amountOfPlayers);
		calculateWords(player, amountOfPlayers);
		cout << "Done?" << endl;
		string done;
		cin >> done;
		if(done == "done") {
			break;
		}
		sayTheScore(player, amountOfPlayers);
	}
}

bool checkForWinner(int x, vector<typep>& player, int& amountOfPlayers) {
	int highest = player[0].score;
	for(int i=1; i<amountOfPlayers; i++) {
		if(player[i].score > highest) {
			highest = player[i].score;
		}
	}
	if(x == highest) {
		return true;
	} else {
		return false;
	}
}
