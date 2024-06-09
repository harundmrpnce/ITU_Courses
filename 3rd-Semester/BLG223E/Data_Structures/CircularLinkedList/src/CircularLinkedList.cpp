#include <iostream>
#include "CircularLinkedList.h"

using namespace std;

CircularLinkedList::CircularLinkedList() {
    head = new Node(-1, true);
    head->setNext(head);
    head->setPrev(head);
}

CircularLinkedList::~CircularLinkedList() {
    Node *itr = head->getNext();
    Node *current = head->getNext();

    while (!itr->isSentinel()) {
        current = itr->getNext();
        delete itr;
        itr = current;
    }
}

void CircularLinkedList::clearList() {
    Node *itr = head->getNext();
    Node *current = head->getNext();

    while (!itr->isSentinel()) {
        current = itr->getNext();
        delete itr;
        itr = current;
    }

    head->setNext(head);
    head->setPrev(head);
}

Node* CircularLinkedList::contains(int data) {
    Node *itr = head->getNext();

    while (!itr->isSentinel() && itr->getData() != data) {
        itr = itr->getNext(); 
    }

    return itr;
}

Node* CircularLinkedList::search(int data) {
    Node *itr = head->getNext();

    if (itr->isSentinel()) {
        return head;
    } else {
        while (itr->getData() <= data) {
            if (itr->getNext()->isSentinel()) return itr;
            itr = itr->getNext();
        }
    }

    return itr->getPrev();
}

void CircularLinkedList::addNode(int data) {
    Node *newNode = new Node(data, false);
    Node *prev = search(data);

    newNode->setNext(prev->getNext());
    newNode->setPrev(prev);
    prev->getNext()->setPrev(newNode);
    prev->setNext(newNode);
}

void CircularLinkedList::removeNode(int data) {
    Node *removed = contains(data);

    if (removed == head) {
        cout << "Element not found\n";
        return;
    }

    Node *prev = removed->getPrev();
    Node *next = removed->getNext();

    prev->setNext(next);
    next->setPrev(prev);
    delete removed;
}

void CircularLinkedList::printList() {
    Node *itr = head->getNext();
    while (itr != head) {
        cout << itr->getData() << " ";
        itr = itr->getNext();
    }
    cout << "\n"; 
}