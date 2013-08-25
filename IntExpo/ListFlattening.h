/* Start at the beginning of the first level */
/* While you are not at the end of the first level */
/*     If the current node has a child */
/*         Append the child to the end of the first level */
/*         Update the tail pointer */
/*     Advance to the next node */
/* void flattenList( Node *head, Node **tail) { */
    Node *curNode = head;
    while( curNode ) {
        // The current node has a child
        if( curNode->child ) {
            append( curNode->child, tail );
        }
        curNode = curNode->next;
    }
}

void append( Node *child, Node **tail) {
    Node *curNode;

    // Append the child child list to the end
    (*tail)->next = child;
    child->prev = *tail;

    // Find the new tail, which is the end of the child child list
    for( curNode = child; curNode->next;
         curNode = curNode->next )
        // Body intentionally empty
        ;

    // Update the tail pointer now that curNode is the new tail
    *tail = curNode;
}


