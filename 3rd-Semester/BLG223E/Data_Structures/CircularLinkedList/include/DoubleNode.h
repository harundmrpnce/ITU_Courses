#pragma once
class Node {
private:
    int data;
    Node *next;
    Node *prev;
    bool sentinel;

public:
    Node(int data, bool sent) {
        this->data = data;
        this->sentinel = sent;
        this->next = nullptr;
        this->prev = nullptr;
    }
    void setData(int);
    int getData();
    void setNext(Node*);
    Node *getNext();
    void setPrev(Node*);
    Node *getPrev();
    bool isSentinel();
};