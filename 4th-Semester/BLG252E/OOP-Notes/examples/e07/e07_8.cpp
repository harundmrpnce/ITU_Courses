// e07_8.cpp
// Default constructors and destructors in inheritance

#include <iostream>
using std::cout;
using std::endl;

// *** Base Class
class Parent {								
public:
	Parent() { cout << "Parent constructor" << endl; }; // Default constructor of the Parent
	~Parent() { cout << "Parent destructor" << endl; }; // Destructor of the Parent
};

// *** The firts derived class
class Child : public Parent {
public:
	Child() { cout << "Child constructor" << endl; }; // Default constructor of the Child
	~Child() { cout << "Child destructor" << endl; }; // Destructor of the Child
};

// *** The second derived Class
class GrandChild : public Child {
public:
	GrandChild() { cout << "GrandChild constructor" << endl; }; // Default constructor of the GrandChild
	~GrandChild() { cout << "GrandChild destructor" << endl; }; // Destructor of the GrandChild
};

// -------- Main Program -------------
int main()
{
	GrandChild grandchild_object;				  // An object of the GrandChild
	cout << "... Program terminates ..." << endl;
	return 0;
}