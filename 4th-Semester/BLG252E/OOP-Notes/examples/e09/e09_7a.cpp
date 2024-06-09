// e09_7a.cpp
// A class template "Stack"
#include <iostream>

// A class template to defie stacks for different types
template <typename T>
class Stack {
public:
    Stack() = default;                  // constructor 
    void push(T);    		            // put a number on the stack 
    T pop();                            // take number off the stack 
    static inline const int MAX{ 100 };
private:
    T m_data[MAX];           	        // array of any type
    unsigned int m_top{};               // index number of top of the stack
};


template<typename T>
void Stack<T>::push(T in) // put number on stack
{
   if(m_top == MAX)                  // if stack full,
     throw "Stack is full!";      // throw exception
   m_data[m_top++] = in;
}

template<typename T>
T Stack<T>::pop()          // take number off stack
{
   if(m_top == 0)                  // if stack empty,
        throw "Stack is empty!"; // throw exception
   else return m_data[--m_top];
}

int main()
{
   Stack<double> s_double;       // s_double is object of class Stack<double>
   
   try{	
   s_double.push(1111.1);       // push 3 doubles, try to pop 4 doubles
   s_double.push(2222.2);
   s_double.push(3333.3);
   std::cout << "1: " << s_double.pop() << std::endl;
   std::cout << "2: " << s_double.pop() << std::endl;
   std::cout << "3: " << s_double.pop() << std::endl;
   std::cout << "4: " << s_double.pop() << std::endl;   // Stack is empty!!
   }
   catch(const char * msg)                    // exception handler
   {
       std::cout << msg << std::endl;
   }

   Stack<long int> s_long;        // s_long is object of class Stack<long int>

   try{	
     s_long.push(123123123L);   // push 3 longs, pop 3 longs
     s_long.push(234234234L);
     s_long.push(345345345L);
     std::cout << "1: " << s_long.pop() << std::endl;
     std::cout << "2: " << s_long.pop() << std::endl;
     std::cout << "3: " << s_long.pop() << std::endl;
   }
   catch(const char * msg)                    // exception handler
   {
       std::cout << msg << std::endl;
   }
	return 0;
}

