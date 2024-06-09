// stack.h for e09_7b
// Definition of the class temlplate Stack
#pragma once

// A class template to defie stacks for different types
template <typename T>
class Stack {
public:
    Stack() = default;                  // default constructor 
    void push(T);    		            // put a number on the stack 
    T pop();                            // take number off the stack 
    static inline const int MAX{ 100 };
private:
	T m_data[MAX]{};           	        // array of any type
    unsigned int m_top{};               // index number of top of the stack
};

template<typename T>
void Stack<T>::push(T in) // put number on stack
{
	if (m_top == MAX)                  // if stack full,
		throw "Stack is full!";      // throw exception
	m_data[m_top++] = in;
}

template<typename T>
T Stack<T>::pop()          // take number off stack
{
	if (m_top == 0)                  // if stack empty,
		throw "Stack is empty!"; // throw exception
	else return m_data[--m_top];
}