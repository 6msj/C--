#include <iostream>

/* Implementation of a stack without using a class. */

struct Element {
    Element * next;
    void * data;
};

bool createStack(Element ** stack);
bool deleteStack(Element ** stack);
bool pop(Element ** stack, void * data); // in pop(), data is an error code to be returned
bool push(Element ** stack, void * data); // in push(), data is the value to be pushed into the stack

int main(void) {
    std::cout << "This program implements a stack." << std::endl;
    // pointer to a stack pointer
    Element ** stack;
    int number = 10;
    if (createStack(stack)) {
        std::cout << "Stack created." << std::endl;
    }

    if(push(stack, (void *)number)) {
        std::cout << "Push successful." << std::endl;
    }
    return 0;
}

bool createStack(Element ** stack) {
    *stack = NULL;
    return true;
}

bool deleteStack(Element ** stack) {
    Element * elem;

    while (*stack) {
        elem = (*stack)->next;
        delete *stack;
        *stack = elem;
    }
    return false;

}

// in pop(), data is an error code to be returned
bool pop(Element ** stack, void ** data) {
    Element * element = new Element;
    if (!(element = *stack)) {
        return false;
    }
    element = *stack;
    *stack = (*stack)->next;
    delete element;
    return false;

}

// in push(), data is the value to be pushed into the stack
bool push(Element ** stack, void * data) {
    Element * element = new Element;
    if (!element) {
        return false; // couldn't allocate memory, return false
    }
    element->data = data;
    element->next = *stack;
    *stack = element;
    return true;
}

