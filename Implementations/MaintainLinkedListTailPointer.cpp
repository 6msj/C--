/* head and tail are global pointers to the first and last element, respectively of a singly-linked list of integers. Implement C functions
 * for the following prototypes: 
 *
 *
 * The argument to remove is the element to be deleted. The two arguments to insertAfter give the data for the new element and the element after which 
 * the new element is to be inserted. It should be possible to insert at the beginning of the list by calling insertAfter with NULL as the element 
 * argument. These functions should return true if successful and false if unsuccessful.*/
#include <iostream>

struct node {
    node * next;
    void * data;
};

class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        bool remove(node *elem);
        bool remove_(node *elem);
        bool insertAfter(node* elem, int data);
        bool insertAfter_(node* elem, int data);
    private:
        node * head;
        node * tail;
};


LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
    return;
}

LinkedList::remove_(node *elem) {
    node *curPos = head;

    if (!elem) {
        return false;
    }

    if (elem == head) {
        head = elem->next;
        delete elem;
    }

    while (curPos) {
        if (curPos->next == elem) {
            curPos->next = elem->next;
            delete elem;
            if (curPos->next == NULL) {
                tail = curPos;
            }
            return true;
        }
        curPos = curPos->next;
    }
    return false;
}

LinkedList::~LinkedList() {
    // implement after
}

bool LinkedList::insertAfter(node * elem, int data) {
    node * prev = head;
    node * next = head->next;
    node * toAdd = new node;
    toAdd->data = (void*)data;

    if (head == elem) {
        if (next) {
            prev->next = toAdd;
            toAdd->next = next;
            tail = next;
        } else {
            next = toAdd;
            tail = next;
        }
    }

    while (next) {
        if (next == elem) {
            if (next->next) {
                toAdd->next = next->next;
                next->next = toAdd;
                return true;
            } else {
                next->next = toAdd;
                tail = next->next;
                return true;
            }
        }
        next = next->next;
    }

    toAdd->next = head;
    head = toAdd;
    return true;

    // find the specific node in the list, if no node is equivalent, insert at the beginning


}

bool LinkedList::remove(node * elem) {
    node * prev = head;
    node * next = head->next;
    if (prev == elem) {
        // special case for head
        head = next;
        delete head;
        return true;
    }
    while (next) {
        if (next == elem) {
            if (next->next) {
                head = next->next;
                delete next;
                return true;
            } else {
                tail = prev;
                delete next;
                return true;
            }
        }
        prev = next;
        next = next->next;
    }
    return false;
}



bool LinkedList::bool insertAfter( node *elem, int data ) { 
    node *newElem, *curPos = head;
    newElem = new node; 
    if( !newElem )
        return false; 
    newElem->data = data;
    /* Insert at beginning of list */ 
    if( !elem ) {
        newElem->next = head; 
        head = newElem;
        /* Special case for empty list */ 
        if( !tail )
            tail = newElem; 
        return true;
    }
    while( curPos ) {
        if( curPos == elem ) {
            newElem->next = curPos->next; 
            curPos->next = newElem;
            /* Special case for inserting at end of list */ 
            if( !(newElem->next) )
                tail = newElem; return true;
        }
        curPos = curPos->next; 
    }
    /* Insert position not found; free element and return failure */ delete newElem;
    return false;
}
