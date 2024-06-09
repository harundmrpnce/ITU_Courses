#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() {
    front = 0;
    back = -1;
    numElements = 0;
}

void Queue::enqueue(int element) {
    if (!isFull()) arr[++back%ARRAY_SIZE] = element;
    numElements++;
}

void Queue::dequeue() {
    if (!isEmpty()) {
        numElements--;
        front++%ARRAY_SIZE;
    }
}

int Queue::frontPeek() {
    if (!isEmpty()) return arr[front];
    else return -1;
}

int Queue::backPeek() {
    if (!isEmpty()) return arr[back];
    else return -1;
}

bool Queue::isEmpty() {
    return numElements == 0;
}

bool Queue::isFull() {
    return numElements == ARRAY_SIZE;
}

void Queue::clear() {
    front = 0;
    back = -1;
    numElements = 0;
}