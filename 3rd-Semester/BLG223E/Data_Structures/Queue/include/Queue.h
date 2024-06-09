const int ARRAY_SIZE = 10;

class Queue {
private:
    int front;
    int back;
    int numElements;
    int arr[ARRAY_SIZE];

public:
    Queue();
    void enqueue(int element);
    void dequeue();
    int frontPeek();
    int backPeek();
    bool isEmpty();
    bool isFull();
    void clear();
};



