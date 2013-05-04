/* Implementation of a Stack using a Link List in a class. */
#include <iostream>

class Stack 
{
public:
    Stack();
    ~Stack();
    void push (void *data);
    void *pop();

private:
    // Element struct needed only internally
    typedef struct Element {
        struct Element *next;
        void *data;
    } Element;
    Element *head;
};

Stack::Stack() {
    head = NULL;
    return;
}

Stack::~Stack() {
    while (head) {
        Element *next = head->next;
        delete head;
        head = next;
    }
    return;
}

void Stack::push(void *data) {
    // Allocation error will throw exception
    Element * elem = new Element;
    elem->data = data;
    elem->next = head;
    head = elem;
    return;
}

void *Stack::pop() {
    Element *popElement = head;
    void * data;
    data = head->data;
    head = head->next;
    delete popElement;
    return data;
}
