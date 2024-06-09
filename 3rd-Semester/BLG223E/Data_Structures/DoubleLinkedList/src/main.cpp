#include <iostream>
#include "DoubleLinkedList.h"


int main() {
    DoubleLinkedList *d = new DoubleLinkedList();
    d->addNode(3);
    d->addNode(12);
    d->addNode(5);
    d->addNode(1);
    
    d->printList();
    d->removeNode(1);
    
    d->printList();
    d->removeNode(0);
    d->removeNode(5);
    
    d->printList();
    d->removeNode(12);
    
    d->printList();
    d->removeNode(3);
    
    d->printList();
    
    return 0;
}