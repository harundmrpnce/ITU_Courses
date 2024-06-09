#include <iostream>
#include "Stack.h"

using namespace std;

Stack::Stack() {
    top = -1;
}

void Stack::push() {
    if (!isFull()) arr[++top] = top;
    else cout << "List is full\n";
}

void Stack::pop() {
    if (!isEmpty()) --top;
    else cout << "List is empty\n";
}

int Stack::peek() {
    if (!isEmpty()) return arr[top];
    else cout << "List is empty\n";
}

bool Stack::isEmpty() {
    return top == -1; 
}

bool Stack::isFull() {
    return top == ARRAY_SIZE - 1;
}

void Stack::clear() {
    top = -1;
}