// e04_17.cpp
// Static Methods
// We can use static methods to acces static data members before we create an object

#include <iostream>
using std::cout;
using std::endl;

class AnyClass {		
public:
	static void setStaticData(int);	// static functions to access static data without objects
	static int getStaticData() { return m_staticData; }

	AnyClass (char);			   // Constructor to initialize the non-stataic data member of AnyClass
	void print() const;			   // const method prints data memebers
	int getNonStaticData() const { return m_nonStaticData; }         // Accessor for x coordinate
	void setNonStaticData(char inData) { m_nonStaticData = inData; }
private:
	static inline unsigned int m_staticData{};  // static data member
	char m_nonStaticData{};	                     // non-static data member
};

// ***** Bodies of Member Functions *****

// static method to set the static data member 
void AnyClass::setStaticData(int in_Data) {
	m_staticData = in_Data;
}

// Constructor to initialize the non-stataic data member of AnyClass
AnyClass::AnyClass(char in_Data) : m_nonStaticData{in_Data}
{}

// A const method to print the memebers of AnyClass
void AnyClass::print() const
{
	cout << "static data= " << m_staticData << " non-static data = " << m_nonStaticData << endl;
}

// -------- Main Program -------------
int main()
{
	// We can access the satatic data before an object has been created
	AnyClass::setStaticData(100);			// static data member is set to 100 for all objects of AnyClass
	cout << "common stataic data = " << AnyClass::getStaticData() << endl; // we can read static data without any object

	cout << "----------------------" << endl; // Seperator
	AnyClass obj1{ 'A' };
	obj1.print();         // print members of obj1

	AnyClass obj2{'B'};
	obj2.print();         // print members of obj2, stataic data is the same

	cout << "----------------------" << endl; // Seperator
	AnyClass::setStaticData(200);			// static data member is set to 200 for all objects of AnyClass
	cout << "common stataic data = " << AnyClass::getStaticData() << endl; // we can read static data using the class name

	cout << "----------------------" << endl; // Seperator
	obj1.print();         // print members of obj1
	obj2.print();         // print members of obj2

	return 0;
}