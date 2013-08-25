/* Start two pointers at the head of the list */
/* Loop infinitely */
/*     If the fast pointer reaches a NULL pointer */
/*         Return that the list is NULL terminated */
/*     If the fast pointer moves onto or over the slow pointer */
/*         Return that there is a cycle */
/*     Advance the slow pointer one node */
/*     Advance the fast pointer two nodes */

// Takes a pointer to the head of a linked list and determines if the list ends in a cycle or is NULL terminated

bool determineTermination( Node *head ) {
    Node *fast, *slow;
    fast = slow = head;
    while( true ) {
        if( !fast || !fast->next )
            return false;
        else if( fast == slow || fast->next == slow )
            return true;
        else {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
}
