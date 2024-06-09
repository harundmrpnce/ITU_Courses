#include "DoubleNode.h"

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

void Node::setPrev(Node* prev) {
    this->prev = prev;
}

Node *Node::getPrev() {
    return this->prev;
}

bool Node::isSentinel() {
    return this->sentinel;
}