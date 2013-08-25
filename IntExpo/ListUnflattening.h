/* Explore path: */
/* While not at the end */
/*     If current node has a child */
/*         Separate the child from its previous Node */
/*         Explore path beginning with the child */
/*     Go onto the next node */

// This is a wrapper function that also updates the tail pointer.
void unflatten( Node *start, Node *tail ) {
    Node *curNode;
    exploreAndSeparate( start );
    // Update the tail pointer
    for( curNode = start; curNode->next; curNode = curNode->next)
        // Body intentionally empty
        ;
    *tail = curNode;
}
        

void exploreAndSeparate( Node *childListStart ) {
    Node *curNode = childListStart;

    while( curNode ) {
        if( curNode->child ) {
            // terminates the child list before the child
            curNode->child->prev->next = NULL;
            // starts the child list beginning with the child
            curNode->child->prev = NULL;
            exploreAndSeparate( curNode->child );
        }
        curNode = curNode->next;
    }
}
