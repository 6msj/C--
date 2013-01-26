// backtracking pseudocode


bool Solve(configuration conf) {
    if (no more choices) // base case
        return (conf is goal state);

    for (all available choices) {
        try one choice c;
        // solve from here, if it w orks out, you're done
        //
        if (Solve(conf with choice c made)) return true;
        unmake choice c;
    }

    return false; // tried all choices, no soln found

    
}
