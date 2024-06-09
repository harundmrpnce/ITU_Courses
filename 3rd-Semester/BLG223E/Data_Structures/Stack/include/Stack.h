const int ARRAY_SIZE = 10;

class Stack {
private:
    int top;
    int arr[ARRAY_SIZE];

public:
    Stack();
    void push();
    void pop();
    int peek();
    bool isEmpty();
    bool isFull();
    void clear();
};

    
