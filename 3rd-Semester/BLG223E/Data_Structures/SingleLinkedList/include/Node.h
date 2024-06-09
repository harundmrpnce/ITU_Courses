#pragma once
class Node {
private:
    int data;
    Node *next;

public:
    Node(int);
    ~Node();
    void setData(int);
    int getData();
    void setNext(Node*);
    Node *getNext();
};