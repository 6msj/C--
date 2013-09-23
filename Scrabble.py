print "Welcome to the Scrabble Calculator"

""" functions """
# word list changes values 
def userEnterWords(numPlayers):
    for i in range (int(numPlayers)):
        word[i] = raw_input("Enter a word.")
    print word

# for every character in the list, send it into a value returning function
# that returns a value that will get added to the total
def addToTotal(name, word, total, numPlayers):
    for i in range(int(numPlayers)):
        for character in word[i]:
            total[i] += returnPoints(character)

def printCurrentScore(name, total, numPlayers):
    for i in range(int(numPlayers)):
        print name[i], "has", total[i], "."
        
# long ifelse statement that give scrabble values
def returnPoints(x):
    if x == 'e' or x == 'a' or x == 'i' or x == 'o' or x == 'n':
        return 1
    if x == 'r' or x == 't' or x == 'l' or x == 's' or x == 'u':
        return 1
    if x == 'd' or x == 'g':
        return 2
    if x == 'b' or x == 'c' or x == 'm' or x == 'p':
        return 3
    if x == 'f' or x == 'h' or x == 'v' or x == 'w' or x == 'y':
        return 4
    if x == 'k':
        return 5
    if x == 'j' or x == 'x':
        return 8
    if x == 'q' or x == 'z':
        return 10
    if x == '_':
        return 0
    if x == 'Q' or x == 'Z':
        return 20
    if x == 'J' or x == 'X':
        return 16
    if x == 'K':
        return 10
    if x == 'F' or x == 'H' or x == 'V' or x == 'W' or x == 'Y':
        return 8
    if x == 'B' or x == 'C' or x == 'M' or x == 'P':
        return 6
    if x == 'D' or x == 'G':
        return 4
    if x == 'T' or x == 'L' or x == 'S' or x == 'U':
        return 2
    if x == 'E' or x == 'A' or x == 'I' or x == 'O' or x == 'N' or x == 'R':
        return 2

# returns true if users enter yes, ends the game
def usersAreQuitting():
    userChoice = raw_input("Is the game done? (y/n)")
    if userChoice == 'y':
        return True
    elif userChoice == 'n':
        return False
    else:
        userChoice == raw_input("You didn't enter anything. Enter again.")
        while userChoice != 'y' or userChoice != 'n':
            userChoice == raw_input("You didn't enter anything. Enter again.")

# declare the winner 
def declareWinner(name, total, numPlayers):
    highest = total[0]
    counter = 0 # checks for draws
    for i in range(1,int(numPlayers)):
        if highest < total[i]:
            highest = total[i]
    for i in range(int(numPlayers)):
        if highest == total[i]:
            print name[i], "has the highest score."
            counter = counter + 1
    if counter > 1:
        print "There is more than one winner."

""" Main """
numPlayers = raw_input("How many players are playing? ")
name = [] #list declaration
word = ["nothing", "nothing", "nothing", "nothing"] #list of words
total = [0, 0, 0, 0] #everyone starts with 0 points

for i in range(int(numPlayers)):# int(numPlayers) gets the interger value of raw_input
    nameVariable = raw_input("Enter your name. ")
    name.append(nameVariable)

print name

while True:
    userEnterWords(numPlayers)
    addToTotal(name, word, total, numPlayers) #processes words to points and adds them to totals
    printCurrentScore(name, total, numPlayers)
    if(usersAreQuitting()):
        break

declareWinner(name, total, numPlayers)



