#pragma once
#include "DoubleNode.h"

class DoubleLinkedList {
private:
    Node* head;
    Node* tail;
    Node* search(int);

public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    Node *contains(int);
    void clear();
    void addNode(int);
    void removeNode(int);
    void printList();
};