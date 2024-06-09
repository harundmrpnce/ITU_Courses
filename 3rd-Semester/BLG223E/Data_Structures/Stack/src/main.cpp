#include <iostream>
#include "Stack.h"

using namespace std;

int main() {
    Stack s;
    
    s.push();
    s.push();
    s.push();
    s.push();
    s.push();
    s.push();
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    s.pop();
    cout << s.peek() << "\n";
    s.pop();

    return 0;
}
