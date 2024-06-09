#include <iostream>
#include "CircularLinkedList.h"


int main() {
    CircularLinkedList *c = new CircularLinkedList();

    c->addNode(1);
    c->addNode(12);
    c->addNode(4);
    c->addNode(0);
    c->addNode(19);
    c->removeNode(19);
    c->removeNode(4);
    c->removeNode(0);
    c->removeNode(1);

    c->printList();

    delete c;

    return 0;
}