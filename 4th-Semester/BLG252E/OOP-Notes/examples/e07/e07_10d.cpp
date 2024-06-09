// e07_10d.cpp
// The owners contain pointers to part objects
// Constructors and destructors
// The programmer can determine and change the order of the creation between owner and the part
// The part objects can be initialized using the data members of the owners, if necessary

#include <iostream>
using std::cout;
using std::endl;

// *** Part Class for Parent
// Defines objects that belong to Parent
class PartForParent {
public:
	PartForParent(int in_data) :m_data{ in_data } {		// Constructor of the Part for Parent
		cout << "PartForParent constructor" << endl;
	}
	~PartForParent() { cout << "PartForParent destructor" << endl; } // Destructor of the Part for Parent. Unnecessary
	void print() const { cout << "Data of PartForParent = " << m_data << endl; }
private:
	int m_data{};                                     // data of the part
};


// *** Base Class
class Parent {
public:
	Parent(int);									// Constructor of the Parent
	~Parent(); 											// Destructor of the Parent
	void print() const;
private:
	PartForParent* m_part;				// Parent contains a pointer to the part object
	int m_data{};					    // data of Parent
};

// Constructor of the Parent
Parent::Parent(int in_data1)
       :m_data{ in_data1 }									// The data member is initialized
{
	cout << "Parent constructor" << endl;						// The body of the constructor
	m_part = new PartForParent{ m_data };				    // The part object is created and initialized using the ata member
}

// Destructor of the Parent
Parent::~Parent() {
	delete m_part;											// Delete the part object
	cout << "Parent destructor" << endl;
}	

// Print function of the Parent
void Parent::print() const {
	m_part->print();
	cout << "Data of Parent = " << m_data << endl;
}

// *** Part Class for Child
// Defines objects that belong to Child
class PartForChild {
public:
	PartForChild(int in_data) :m_data{ in_data } {				// Constructor of the Part for Child
		cout << "PartForChild constructor" << endl; }
	~PartForChild() { cout << "PartForChild destructor" << endl; } // Destructor of the Part for Child. Unnecessary
	void print() const { cout << "Data of PartForChild = " << m_data << endl; }
private:
	int m_data{};		// data of the part
};


// *** The Derived Class
class Child : public Parent {
public:
	Child(int, int);			// Constructor of the Child
	~Child() ;							// Destructor of the Child
	void print() const;
private:
	PartForChild *m_part;         // Child contains a pointer to the part object
	int m_data{};				  // data of Child
};

// Constructor of the Child
Child::Child(int in_data1, int in_data2)      // Constructor of the Child
	: Parent{ in_data1 },												// Intialize the Parent subobject
	  m_data{ in_data2 }												// Initialize data memeber
{
	cout << "Child constructor" << endl;									// The body of the constructor
	m_part = new PartForChild{ m_data };								// Create the part object and itialize using the data member
};

// Destructor of the Child
Child::~Child() { 
	delete m_part;							// Delete the part object
	cout << "Child destructor" << endl;
};        

// Print function of the Child
void Child::print() const {
	Parent::print();					// Call the print of the Parent (Base)
	m_part->print();					// Call the print of the part
	cout << "Data of Child = " << m_data << endl;
}

// -------- Main Program -------------
int main()
{
	Child child_object{ 1, 2 };				  // An object of the Child
	child_object.print();
	return 0;
}