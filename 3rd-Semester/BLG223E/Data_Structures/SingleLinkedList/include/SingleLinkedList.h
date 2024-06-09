#pragma once
#include "Node.h"

class SingleLinkedList {
private:
    Node* head;
    Node* tail;
    Node* search(int);

public:
    SingleLinkedList();
    ~SingleLinkedList();
    void clear();
    void addNode(int);
    void removeNode(int);
    void printList();
};