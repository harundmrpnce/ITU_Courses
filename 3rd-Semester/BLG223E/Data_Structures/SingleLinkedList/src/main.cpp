#include <iostream>
#include "SingleLinkedList.h"


int main() {

    SingleLinkedList *s = new SingleLinkedList();
    s->addNode(3);
    s->addNode(12);
    s->addNode(5);
    s->addNode(2);
    s->addNode(1);
    
    s->printList();
    delete s;

    // Node *head;
    // head = new Node(5);
    // head->setNext(new Node(10));
    // head->getNext()->setNext(new Node(15));


    return 0;
}