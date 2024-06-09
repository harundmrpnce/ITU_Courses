#include <iostream>
#include "DoubleLinkedList.h"

using namespace std;

DoubleLinkedList::DoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
}

DoubleLinkedList::~DoubleLinkedList() {
}

Node* DoubleLinkedList::search(int data) {
    Node *itr = head;
    while ((itr != nullptr) && (itr->getData() < data)) {
        itr = itr->getNext();
    }
    return itr;
}

Node* DoubleLinkedList::contains(int data) {
    Node *itr = head;
    while ((itr != nullptr) && (itr->getData() != data)) {
        itr = itr->getNext();
    }
    return itr;
}

void DoubleLinkedList::clear() {
    if (head != nullptr) {
        delete head;
    }
    head = nullptr;
    tail = nullptr;
}

void DoubleLinkedList::addNode(int data) {
    Node *newNode = new Node(data);

    if (head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        Node *itr = head;
        Node *searched = search(data);
        if (searched == head) {
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        } else if (searched == nullptr) {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        } else {
            newNode->setNext(searched);
            newNode->setPrev(searched->getPrev());
            searched->getPrev()->setNext(newNode);
            searched->setPrev(newNode);
        }
    }
}

void DoubleLinkedList::removeNode(int data) {
    Node *removed = contains(data);

    if (removed == nullptr) {
        cout << "The removed node is not in the list\n";
        return;
    } 
    if (head == tail) {
        delete removed;
        head = nullptr;
        tail = nullptr;
    } else {
        if (removed == head) {
            head = head->getNext();
            head->setPrev(nullptr);
            removed->setNext(nullptr);
        } else if (removed == tail) {
            tail = tail->getPrev();
            tail->setNext(nullptr);
            removed->setPrev(nullptr);
        } else {
            Node* prev = removed->getPrev();
            Node* next = removed->getNext();
            prev->setNext(next);
            next->setPrev(prev);
            removed->setNext(nullptr);
            removed->setPrev(nullptr);
        }
        delete removed;
    }
}

void DoubleLinkedList::printList() {
    Node *itr = head;
    while (itr != NULL) {
        cout << itr->getData() << " ";
        itr = itr->getNext();
    }
    cout << "\nEnd of the list\n";   
}