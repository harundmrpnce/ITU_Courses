#include "DoubleNode.h"

Node::Node(int data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
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

void Node::setPrev(Node* prev) {
    this->prev = prev;
}

Node *Node::getPrev() {
    return this->prev;
}