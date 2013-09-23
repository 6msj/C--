/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the KarelGoesHome problem.
 */

#include <iostream>
#include <iomanip>
using namespace std;

/* Function prototypes */

int countPaths(int street, int avenue);
int countPaths__(int street, int avenue); 


int __countPaths__solution2(int street, int avenue);

/* Main program */

int main() {
   // [Fill this in with a test program]
   cout << countPaths(2, 3) << endl;
   return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

int countPaths(int street, int avenue) {
   return countPaths__(street, avenue);
}


int countPaths__(int street, int avenue) {
    if(street == 1 && avenue == 1) {
        return 0;
    }

    if(street >= 2) {
        return 1 + countPaths__(street-1, avenue);
    }

    if(avenue >= 2) {
        return 1 + countPaths__(street, avenue-1);
    }

    return 0;
        
}

int __countPaths__solution2(int street, int avenue) {
    if (street == 1 || avenue == 1) {
      return 1;
   } else {
      return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
   }
}
 

