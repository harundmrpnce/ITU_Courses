// e07_10a.cpp
// Inheritance and composition
// Constructors and destructors
// All classes have default constructors

#include <iostream>
using std::cout;
using std::endl;

// *** Part Class for Parent
// Defines objects that belong to Parent
class PartForParent {
public:
	PartForParent() {								// Default Constructor of the Part for Parent. 
		cout << "PartForParent constructor" << endl;
	} 
	~PartForParent() { cout << "PartForParent destructor" << endl; } // Destructor of the Part for Parent. Unnecessary
	void print() const { cout << "Data of PartForParent = " << m_data << endl; }
private:
	int m_data{1};                                     // data of the part
};

// *** Base Class
class Parent {								
public:
	Parent() {									// Default Constructor of the Parent
		cout << "Parent constructor" << endl;						
	}
	~Parent() { cout << "Parent destructor" << endl; }	// Destructor of the Parent. Unnecessary
	void print() const;
private:
	PartForParent m_part;				// Parent contains (has) a part 
	int m_data{2};					    // data of Parent
};

// Print function of the Parent
void Parent::print() const {
	m_part.print();
	cout << "Data of Parent = " << m_data << endl;
}

// *** Part Class for Child
// Defines objects that belong to Child
class PartForChild {
public:
	PartForChild() {									// Default Constructor of the Part for Child
		cout << "PartForChild constructor" << endl;
	}
	~PartForChild() { cout << "PartForChild destructor" << endl; } // Destructor of the Part for Child. Unnecessary
	void print() const { cout << "Data of PartForChild = " << m_data << endl; }
private:
	int m_data{3};		// data of the part
};


// *** The Derived Class
class Child : public Parent {
public:
	Child(){								// Default Constructor of the Child
		cout << "Child constructor" << endl;									  // The body of the constructor
	}
	~Child() { cout << "Child destructor" << endl; }        // Destructor of the Child. Unnecessary
	void print() const;
private:
	PartForChild m_part;         // Child contains (has) a part 
	int m_data{4};				 // data of Child
};

// Print function of the Child
void Child::print() const {
	Parent::print();					// Call the print of the Parent (Base)
	m_part.print();					// Call the print of the part
	cout << "Data of Child = " << m_data << endl;
}

// -------- Main Program -------------
int main()
{
	Child child_object{};				  // An object of the Child
	child_object.print();
	return 0;
}