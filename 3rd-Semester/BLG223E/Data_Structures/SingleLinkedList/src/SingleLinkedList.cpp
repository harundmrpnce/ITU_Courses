#include <iostream>
#include "SingleLinkedList.h"

using namespace std;

SingleLinkedList::SingleLinkedList() {
    head = nullptr;
    tail = nullptr;
}

SingleLinkedList::~SingleLinkedList() {
    if (head != nullptr) delete head;
}

Node* SingleLinkedList::search(int data) {
    Node *itr = head;
    if (data < itr->getData() || data == itr->getData()) {
        return nullptr;
    } else {
        while (itr->getNext() != nullptr) {
            if (data > itr->getNext()->getData()) {
                itr = itr->getNext();
            } else {
                break;
            }
        }
        return itr;
    }
}

void SingleLinkedList::clear() {
    if (head != nullptr) {
        delete head;
    }
    head = nullptr;
    tail = nullptr;
}

void SingleLinkedList::addNode(int n) {
    Node *newNode = new Node(n);
    if (head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        Node *prevNode = this->search(n);
        if (prevNode == nullptr) {
            newNode->setNext(head);
            head = newNode;
        } else {
            if (prevNode->getNext() == nullptr) {
                prevNode->setNext(newNode);
                tail = newNode;
            } else {
                newNode->setNext(prevNode->getNext());
                prevNode->setNext(newNode);
            }
        }
    }
}

void SingleLinkedList::removeNode(int n) {
    Node *prevNode = search(n);
    if ((head == tail) && (head != nullptr) && (tail != nullptr)) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else if (head != nullptr) {
        if (prevNode == nullptr) {
            Node *temp = head;
            head = temp->getNext();
            temp->setNext(nullptr);
            delete temp;
        } else if (prevNode->getNext() == tail) {
            tail = prevNode;
            delete tail->getNext();
            tail->setNext(nullptr);
        } else {
            Node* temp = prevNode->getNext();
            prevNode->setNext(temp->getNext());
            temp->setNext(nullptr);
            delete temp;
        }
    } else {
        cout << "The list is empty\n";
    }
}

void SingleLinkedList::printList() {
    Node *itr = head;
    while (itr != nullptr) {
        cout << itr->getData() << endl;
        itr = itr->getNext();
    }   
}