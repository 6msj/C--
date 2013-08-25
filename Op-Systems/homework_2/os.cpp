#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

typedef std::string word;

// Shared variables
pthread_mutex_t a_mutex;
std::ifstream in; // object to read from the file
std::ofstream out; // object to write to the file
std::deque<word> playDeque; // play pops to rewind, reading forward
std::deque<word> rewindDeque; // rewind inserts to play, reading backwards
bool currentlyPlaying; // boolean value to determine player status
float playbackRate; // negative goes in reverse, positive forward
char controlOption; // variable control threads set
bool currentlyThreading; // keyboard thread controls when other threads exit

// Helper Methods
void loadWordsInDeque();
void askThenSeek();
void askThenLoad();
void askThenRate();

// Player Thread Functions
void changeFunction();
void togglePlayer();
void LoadFile(const char *filename);
void Stop();
void Start();
void Rewind();
void SeekTo(int byteoffset);
void SetRate(float rate);
void * playMedia(void *data);
void playWordFromMedia(std::deque<word> &playFrom, std::deque<word> &addTo);
void attemptStart(std::deque<word> &dequeToCheck);

// Controller Thread Functions
int determineSleep();
void * stopSometimes(void *data);
void * startSometimes(void *data);
void * getKeys(void *data);

int main() {
    // Initialize defaults
    currentlyThreading = true;
    currentlyPlaying = false; // starts in STOP mode
    std::string filename = "text.txt";
    LoadFile(filename.c_str());
    playbackRate = 1; // default rate is 1 second

    // Initialize pthreads
    pthread_mutex_init(&a_mutex, NULL);

    // thread ids
    long autostopid, autostartid, keythreadid, playthreadid; // 64 bit
    autostopid = autostartid = keythreadid = playthreadid = 0;

    // thread structures
    pthread_t auto_stop;
    pthread_t auto_start;
    pthread_t key_thread;
    pthread_t play_thread;

    // create threads
    autostopid = pthread_create(&auto_stop, NULL, stopSometimes, (void*)autostopid);
    autostartid = pthread_create(&auto_start, NULL, startSometimes, (void*)autostartid);
    keythreadid = pthread_create(&key_thread, NULL, getKeys, (void*)keythreadid);
    playthreadid = pthread_create(&play_thread, NULL, playMedia, (void*)playthreadid);
    
    // wait for threads to finish
    pthread_join(auto_stop, NULL);
    pthread_join(auto_start, NULL);
    pthread_join(key_thread, NULL);
    pthread_join(play_thread, NULL);

    return 0;
}

void * getKeys(void *data) {
    while(currentlyThreading) {
        pthread_mutex_lock(&a_mutex);
        std::cout << "\n***********************" << std::endl;
        std::cout << "' ' - Toggle\n'r' - Rewind\n's' - Seek\n'l' - Load\n't' - Rate\n'x' - Quit\n||>";
        std::cout << "***********************" << std::endl;
        pthread_mutex_unlock(&a_mutex);
        std::cin.get(controlOption);
        std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "\nYou chose :" << controlOption << ":" << std::endl;
        changeFunction();
        sleep(2); // wait a bit before displaying the menu again
    }

    pthread_exit(NULL);
}

void * stopSometimes(void *data) {
    while(currentlyThreading) {
        sleep(determineSleep()); 
        Stop();
    }
    pthread_exit(NULL);
}

void * startSometimes(void *data) {
    while(currentlyThreading) {
        sleep(determineSleep()); 
        Start();
    }
    pthread_exit(NULL);
}

int determineSleep() {
    int max = 30;
    int min = 5;
    srand(time(NULL));
   	return rand()%(max-min)+min; 
}

// Depending on a variable that the control thread sets, player thread uses a different function.
void changeFunction() {
    switch(controlOption) {
    case ' ': togglePlayer(); break;
    case 'r': Rewind(); break;
    case 's': askThenSeek(); break;
    case 'l': askThenLoad(); break; 
    case 't': askThenRate(); break;
    case 'x': currentlyThreading = false; break;
    default: break;
    }
}

// ' ' (blank) -- toggles the player's mode between 'playing' and 'stopped'
void togglePlayer() {
    if(currentlyPlaying) {
        Stop(); // Stop() will check if it's currently playing again
    } else {
        Start();
    }
}

// Get all the words from the file and load them in a deque. When the deque reads a word, it pops the word to the deque, which allows the player to read backwards.
void loadWordsInDeque() {
    if(!playDeque.empty() || !rewindDeque.empty()) {
        // there's a chance a file was loaded before, so clear both deques before loading new words in
        std::deque<word> _empty;
        std::deque<word> empty_;
        std::swap(playDeque, _empty);
        std::swap(rewindDeque, empty_);
    }

    word newWord;
    in >> newWord;
    while(!in.eof()) {
        playDeque.push_back(newWord);
        if(in.eof()) {
            continue;
        }
        in >> newWord;
    }
    in.close();
}

// 's' -- prompts the user for a time, then seeks the player to that time
void askThenSeek() {
    std::cout << "Seek to when? > ";
    int byteoffset;
    std::cin >> byteoffset;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Seeking to :" << byteoffset << ":" << std::endl;
    SeekTo(byteoffset);
}

// 'l' -- prompts the user for a file, then loads the file into the player
void askThenLoad() {
    std::cout << "Load what file? >";
    std::string filename;
    getline(std::cin, filename);
    LoadFile(filename.c_str());
}

// 't' -- prompts the user for a rate, then uses it to set the player's rate 
void askThenRate() {
    std::cout << "What rate? >";
    float newRate;
    scanf("%f",&newRate);
    std::cout << "\nYou chose the rate :" << newRate << ":" << std::endl;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    SetRate(newRate);
    //printf("%f",newRate);
}

// Prepares the player to playback the file whose name is passed in. Stops the player if currently playing.
void LoadFile(const char *filename) {
    if(in.is_open()) {
        // if a file is already opened, close it before opening another
        in.close();
    }

    in.open(filename, std::ios::in);
    if(!in) {
        std::cout << "Can't open input file." << std::endl;
    } else {
        std::cout << "File opened." << std::endl;
    }

    // after loading the file, put its contents in a deque
    loadWordsInDeque();
}

// Stops the player if currently playing.
void Stop() {
    pthread_mutex_lock(&a_mutex);
    if(currentlyPlaying && currentlyThreading) {
        std::cout << "\n---STOPPING---\n" << std::endl;
        currentlyPlaying = !currentlyPlaying;
    }
    pthread_mutex_unlock(&a_mutex);
}

// Starts the player if currently stopped.
void Start() {
    pthread_mutex_lock(&a_mutex);
    if(!currentlyPlaying && currentlyThreading) {
        if(playbackRate > 0) {
            attemptStart(playDeque);
        } else {
            attemptStart(rewindDeque);
        }
    } else {
        pthread_mutex_unlock(&a_mutex);
    }
}

void attemptStart(std::deque<word> &dequeToCheck) {
    if (dequeToCheck.empty()) {
        pthread_mutex_unlock(&a_mutex);
        std::cout << "\n--- ";
        std::cout << ((playbackRate > 0) ? "[Forward] " : "[Backwards] ");
        std::cout << "TRIED TO START BUT NO MORE WORDS TO DISPLAY---" << std::endl;
    } else {
        std::cout << "\n---STARTING---\n" << std::endl;
        currentlyPlaying = !currentlyPlaying;
        pthread_mutex_unlock(&a_mutex);
    }
}

void * playMedia(void *data) {
    while(currentlyThreading) {
        while(currentlyPlaying) {
            pthread_mutex_lock(&a_mutex);
            if(playbackRate < 0) {
                // play in reverse
                pthread_mutex_unlock(&a_mutex);
                playWordFromMedia(rewindDeque, playDeque);
            } else {
                // play forward
                pthread_mutex_unlock(&a_mutex);
                playWordFromMedia(playDeque, rewindDeque);
            }
        }
    }
    pthread_exit(NULL);
}

void playWordFromMedia(std::deque<word> &playFrom, std::deque<word> &addTo) {
    while(!playFrom.empty() && currentlyPlaying) {
        word playingWord;
        pthread_mutex_lock(&a_mutex);
        float oldPlayBackRate = playbackRate;
        playbackRate > 0 ? playingWord = playFrom.front() : playingWord = playFrom.back();
        std::cout << "\n" << playingWord;
        playbackRate > 0 ? addTo.push_back(playingWord) : addTo.push_front(playingWord);
        playbackRate > 0 ? playFrom.pop_front() : playFrom.pop_back();
        pthread_mutex_unlock(&a_mutex);
        //sleep(std::abs(playbackRate));
        usleep(1.0/(std::abs(playbackRate))*1000000);
        if(playFrom.empty()) {
            std::cout << "\nNo words to display!" << std::endl;
            Stop();
        }
        if(playbackRate != oldPlayBackRate) {
            return;
        }
    }
    Stop();
}


// Sets the position of the player to time 0.
void Rewind() {
    pthread_mutex_lock(&a_mutex);
    while(!rewindDeque.empty()) {
        playDeque.push_front(rewindDeque.back());
        rewindDeque.pop_back();
    }
    pthread_mutex_unlock(&a_mutex);
}

// Sets the position of the player to the closest word boundary past the given byte offset from the start of the file.
void SeekTo(int byteoffset) {
    Rewind();
    bool movingOffset = true;
    while(movingOffset) {
        pthread_mutex_lock(&a_mutex);
        word dequeFront = playDeque.front();
        if(byteoffset < dequeFront.size()) {
            rewindDeque.push_back(dequeFront);
            playDeque.pop_front();
            movingOffset = false;
        } else {
            byteoffset -= dequeFront.size();
            rewindDeque.push_back(dequeFront);
            playDeque.pop_front();
        }
        pthread_mutex_unlock(&a_mutex);
    }
}

// Sets the playback rate: 1.0 is forward at normal speed, -1.0 is reverse, 0.5 is forward at 1/2 speed, etc.
void SetRate(float rate) {
    pthread_mutex_lock(&a_mutex);
    playbackRate = rate;
    pthread_mutex_unlock(&a_mutex);
}




