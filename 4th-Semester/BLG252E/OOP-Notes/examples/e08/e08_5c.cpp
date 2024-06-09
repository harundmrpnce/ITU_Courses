// e08_5c.cpp
// virtual function used as base class destructor 
// In the main function, we create a dynamic object
#include <iostream>
using std::cout;
using std::endl;

class Parent{
public:
  Parent() {										// Constructor allocates memory
	cout << "Parent constructor" << endl;
	m_parentPtr = new int[10];						// Allocates memory for 10 integers
  }   
  virtual ~Parent() {								// Destructor is virtual
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
  ~Child() {										// Destructor is virtual
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
  ~GrandChild() {										// Virtual
	  cout << "GrandChild destructor" << endl;
	  delete[] m_grandChildPtr;							// Deallocates memory
  } 
private:
	int* m_grandChildPtr{};
};

// We create a dynamic object of GrandChild
int main()
{
  Parent* parentPtr{};				        // parentPtr can point to objects of Parent, Child, and GrandChild
  parentPtr = new GrandChild;		        // parentPtr points to a dynamic oject of GrandChild
  cout << "-------------------" << endl;    // line break
  delete parentPtr;                         // delete the dynamic object
  return 0;
}