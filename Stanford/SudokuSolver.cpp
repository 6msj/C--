#include <iostream>
using namespace std;

bool SolveSudoku(Grid<int> &grid);


int main() {
    return 0;

}

bool SolveSudoku(Grid<int> &grid) {
    int row, col;
    if (!FindUnassignedLocation(grid, row, col))
        return true;

    for(int num = 1; num <= 9; num++) { // options are 1-9
        if(NoConflicts(grid, row, col, num)) // if # looks ok {
            grid(row, col) = num; // try assign #
        if (SolveSudoku(grid)) return true;
        grid(row, col) = UNASSIGNED; // undo and try again

        }
    }
    return false;
}


