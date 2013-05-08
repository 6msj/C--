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
        node *findMToLastElement( int m );
    private:
        node * head;
        node * tail;
};


LinkedList::LinkedList() {
    head = NULL;
    tail = NULL;
    return;
}

LinkedList::findMToLastElement( int m ) {
    node *current, *mBehind;
    int i;
    // advance current m elements from beginning, 
    // checking for the end of the list 
    current = head;

    for (i = 0; i < m; i++) {
        if (current->next) {
            current = current->next;
        } else {
            return NULL;
        }
    }

    // start mBehind at beginning and advance pointers
    // together until current hits last element 
    mBehind = head;
    while ( current->next ) {
        current = current->next;
        mBehind = mBehind->next;
    }

    return mBehind;
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
