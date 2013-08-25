#include <iostream>
#include <string>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_INGREDIENTS 3 // number of ingredients we are dealing with
#define MAX_CIGS_SMOKED 30 // max number of cigarettes smoked before program stops

// global mutex for the program, assignment initializes it
pthread_mutex_t a_mutex;
pthread_cond_t a_cond;

// number of cigagrettes the agent enables to be smoked
int SMOKED_CIGS = 0; 

enum ingredient {
    Nothing = 0,
    Paper = 1,
    Match = 2,
    Tobacco = 3
};

struct Table {
    ingredient INGREDIENTS_ON_TABLE [NUM_INGREDIENTS-1]; // there can only be 2 ingredients on a table at a time
}__Table__;

// functions smoker threads use
void * do_smoke(void *data);
void kill_time();
std::string ingredient_name(ingredient number);

// functions agent thread uses
void * watch_table(void *data);
void check_for_ingredient(ingredient thread_ingredient);
ingredient get_random_ingredient();
void add_ingredients_to_table();

int main(void) {
    // start the table with Nothing
    __Table__.INGREDIENTS_ON_TABLE[0] = Nothing;
    __Table__.INGREDIENTS_ON_TABLE[1] = Nothing;

    // initialize mutex and condition variable
    pthread_mutex_init(&a_mutex, NULL);
    pthread_cond_init(&a_cond, NULL);

    // thread Id for smoker threads
    int smokerPaperId;
    int smokerMatchesId;
    int smokerTobaccoId;
    int agentId;

    // thread structures
    pthread_t p_smokPaper;
    pthread_t p_smokMatches;
    pthread_t p_smokTobacco;
    pthread_t p_agent;

    // thread values
    ingredient agentNothing = Nothing; // 0
    ingredient paperHolder = Paper; // 1
    ingredient matchesHolder = Match; // 2
    ingredient tobaccoHolder = Tobacco; // 3

    agentId = pthread_create(&p_agent, NULL, watch_table, (void*)&agentNothing);
    // create the threads that will consume the ingredients if possible
    smokerPaperId = pthread_create(&p_smokPaper, NULL, do_smoke, (void*)&paperHolder);
    smokerMatchesId = pthread_create(&p_smokMatches, NULL, do_smoke, (void*)&matchesHolder);
    smokerTobaccoId = pthread_create(&p_smokTobacco, NULL, do_smoke, (void*)&tobaccoHolder);

    // wait for all threads to complete
    pthread_join(p_smokPaper, NULL);
    pthread_join(p_smokMatches, NULL);
    pthread_join(p_smokTobacco, NULL);
    pthread_join(p_agent, NULL);

    std::cout << "30 Cigarettes have been smoked." << std::endl;

    // clean up and exit
    pthread_mutex_destroy(&a_mutex);
    pthread_cond_destroy(&a_cond);
    pthread_exit(NULL);

    std::cout << "THIS WON'T PRINT!!" << std::endl;
    return 0;
}

void * watch_table(void *data) {
    pthread_mutex_lock(&a_mutex);
    while (SMOKED_CIGS < MAX_CIGS_SMOKED) {
        //check if mutex is locked
            // if locked, check to see if array is empty
                // if empty, add to the table, making sure to lock the mutex/table 
        // once table is empty, add ingredients to the table
        if (__Table__.INGREDIENTS_ON_TABLE[0] == Nothing && __Table__.INGREDIENTS_ON_TABLE[1] == Nothing) {
            add_ingredients_to_table();
        }
        pthread_cond_wait(&a_cond, &a_mutex);
    }
    pthread_mutex_unlock(&a_mutex);
    pthread_exit(NULL);
}

void add_ingredients_to_table() {
    std::cout << "Adding ingredients to table!" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    __Table__.INGREDIENTS_ON_TABLE[0] = get_random_ingredient();
    __Table__.INGREDIENTS_ON_TABLE[1] = get_random_ingredient();
    // change the ingredient until the ingredients are different
    while (__Table__.INGREDIENTS_ON_TABLE[0] == __Table__.INGREDIENTS_ON_TABLE[1]) {
        __Table__.INGREDIENTS_ON_TABLE[1] = get_random_ingredient();
    }
}

ingredient get_random_ingredient() {
    srand(time(NULL));
    // Between 3 and 1
    int randNumber = rand() % 3 + 1;
    if (randNumber == 3) {
        return Tobacco;
    } else if (randNumber == 2) {
        return Match;       
    } else {
        return Paper;
    }
}

void * do_smoke(void *data) {
    // Check thread's ingredient against Table's ingredients.
 
    ingredient thread_ingredient = *((ingredient*)data);

    while (true) {
        kill_time();
        check_for_ingredient(thread_ingredient);
        if (SMOKED_CIGS == MAX_CIGS_SMOKED) {
            break;
        }
        sleep(5);
    }

    // terminate the thread
    pthread_exit(NULL);
}

void kill_time() {
    for (int i = 0; i < 10000000; i++) {
        ;
    }
}

void check_for_ingredient(ingredient thread_ingredient) {
    bool doesnthaveingredient = true;
    while (doesnthaveingredient) {
        if (SMOKED_CIGS == MAX_CIGS_SMOKED) {
            return;
        }
        int sum = thread_ingredient; // each thread has its own ingredint value, so to get a match, it has to reach 6
        for (int i=0; i<NUM_INGREDIENTS-1; i++) {
            sum += __Table__.INGREDIENTS_ON_TABLE[i];
        }
        if (sum == 6) {
            // smoker about to smoke, lock the mutex as smoker takes the ingredients
            pthread_mutex_lock(&a_mutex);
            doesnthaveingredient = false;
            for (int i = 0; i < NUM_INGREDIENTS-1; i++) {
                __Table__.INGREDIENTS_ON_TABLE[i] = Nothing;
            }
        }
    }

    // kill some time while smoker is smoking
    kill_time();
    std::cout << "A Smoker Started Smoking!" << std::endl;
    kill_time();

    std::cout << "Smoker with ingredient: " << ingredient_name(thread_ingredient) << " finished Smoking!" << std::endl;
    std::cout << "--------------------------" << std::endl;

    doesnthaveingredient = true; // after the smoker finished do_smoke, they need the ingredients again
    SMOKED_CIGS++; 
    // smoker finished do_smoke, unlock the mutex
    pthread_mutex_unlock(&a_mutex);
    // tell the agent the smoker finished
    pthread_cond_signal(&a_cond); 
}

std::string ingredient_name(ingredient number) {
    if (number == 1) {
        return "Paper";
    } else if (number == 2) {
        return "Match";
    } else {
        return "Tobacco";
    }
}

