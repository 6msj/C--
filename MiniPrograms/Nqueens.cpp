#include <iostream>
using namespace std;

bool Solve(Grid<bool> &board, int col);

int main() {
    return 0;
}

bool Solve(Grid<bool> &board, int col) {
    if (col >= board.numCols()) return true; // base case

    for (int rowToTry=0; rowToTry<board.numRows(); rowToTry++) {
        if (IsSafe(board.rowToTry, col)) {
            PlaceQueen(board, rowToTry, col);
            if(Solve(board, col+1)) return true;
            RemoveQueen(board, rowToTry, col);
        }
    }
    return false;
}
