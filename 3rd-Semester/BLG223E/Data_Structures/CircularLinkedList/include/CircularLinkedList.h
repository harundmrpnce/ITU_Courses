#pragma once
#include "DoubleNode.h"

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList();
    ~CircularLinkedList();
    void clearList();
    Node *contains(int);
    Node *search(int);
    void addNode(int);
    void removeNode(int);
    void printList();
};