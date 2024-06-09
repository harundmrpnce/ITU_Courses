#include "Node.h"

Node::Node(int data) {
    this->data = data;
    this->next = nullptr;
}

Node::~Node() {
    if (next != nullptr) {
        delete next;  
    }
}

void Node::setData(int data) {
    this->data = data;
}

int Node::getData() {
    return this->data;
}

void Node::setNext(Node* next) {
    this->next = next;
}

Node *Node::getNext() {
    return this->next;
}