#pragma once
class Node {
private:
    int data;
    Node *next;
    Node *prev;

public:
    Node(int);
    ~Node();
    void setData(int);
    int getData();
    void setNext(Node*);
    Node *getNext();
    void setPrev(Node*);
    Node *getPrev();
};