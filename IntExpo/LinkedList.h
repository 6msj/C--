#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>

struct Node {
    Node *next;
    int data;
};

class LinkedList {
public:
    LinkedList();
    void pop();
    void push(int data);
private:
    Node *head;
};

#endif
