// e08_5a.cpp
// non-virtual function used as base class destructor 
// In the main function, we create an automatic object (not dynamic)
#include <iostream>
using std::cout;
using std::endl;

class Parent{
public:
  Parent() {										// Constructor allocates memory
	cout << "Parent constructor" << endl;
	m_parentPtr = new int[10];						// Allocates memory for 10 integers
  }   
  ~Parent() {										// Destructor is not virtual
	  cout << "Parent destructor" << endl;
	  delete[] m_parentPtr;							// Deallocates memory
  }  
private:
	int* m_parentPtr{};
};

class Child : public Parent{
public:
	Child() {										// Constructor allocates memory
		cout << "Child constructor" << endl;
		m_childPtr = new int[10];					// Allocates memory for 10 integers
	}
  ~Child() {										// Destructor is not virtual
	  cout << "Child destructor" << endl;
	  delete[] m_childPtr;							// Deallocates memory
  }   
private:
	int* m_childPtr{};
};

class GrandChild : public Child{
public:
	GrandChild() {										// Constructor allocates memory
	cout << "GrandChild constructor" << endl;
	m_grandChildPtr = new int[10];					   // Allocates memory for 10 integers
  }
  ~GrandChild() {										// Non-virtual
	  cout << "GrandChild destructor" << endl;
	  delete[] m_grandChildPtr;							// Deallocates memory
  } 
private:
	int* m_grandChildPtr{};
};

// We create an automatic object (not dynamic) of GrandChild
int main()
{
  GrandChild grandChildObj;					  // grandChildObj is an automatic (not dynamic) oject of GrandChild
  cout << "Program terminates ..." << endl;   
  return 0;
}