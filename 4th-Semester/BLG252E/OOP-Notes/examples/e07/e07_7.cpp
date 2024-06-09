// e07_7.cpp
// Overloading and Name hiding
// Redefining data members
// Changing the parameters of the Base methods during redefinition

#include <iostream>
#include <string>
using std::cout;
using std::endl;

// *** Base Class
class Base {								
public:
	void method() const;          // Method of Base without parameters
	void method(int) const;		  // Overloading: Method of base with different parameters
	void notRedefined() const;    // Will not be Redefined
protected:
	int m_data1 {1}; 	     // protected integer data member of Base
private:
	int m_data2 {2};         // private integer data member of Base
};

// ***** Bodies of Member Functions of the Base class *****

 // Method of Base without parameters
void Base::method() const {
	cout << "Method of Base without parameters" << endl;
}

// Method of Base with an integer parameter
void Base::method(int in_i) const {
	cout << "Method of Base with an integer parameter" << endl;
}

// This method of Base will not be redefined
void Base::notRedefined() const {
	cout << "This method of Base is not redefined" << endl;
}

// *** The Derived Class
class Derived : public Base {
public:
	void method(const std::string &) const;         // Name Hiding : Methods of Base are redefined
private:
	std::string m_data1 { "ABC" };					// protected integer data member of Base is redefined as a string, it is a new member
	int m_data2 {3};								// private integer data member of Base is redefined, it is a new member
};

// Method of Derived
void Derived::method(const std::string& in_str) const {
	cout << "Method of Derived: " << in_str << endl;
	cout << "m_data1 of Derived = " << m_data1 << endl;			// m_data of Derived
	cout << "m_data1 of Base = " << Base::m_data1 << endl;		// OK. m_data1 of Base is protected
	cout << "m_data2 of Derived = " << m_data2 << endl;			// m_data2 of Derived
	//cout << "m_data2 of Base = " << Base::m_data2 << endl;	// Error! m_data2 of Base is private
	Base::method();											    // OK. method() of Base is public or protectd
	Base::method(5);									    // OK. method(int) of Base is public or protectd (overloading)
	notRedefined();											// OK. not-redefined method of Base
}

// -------- Main Program -------------
int main()
{
	Derived derived_object;				  // An object of Derived
	derived_object.method("XYZ");  // method(const std::string&) of Derived

	//derived_object.method();			 // Error! Redefined
	//derived_object.method(5);		     // Error! Redefined
	
	cout << "----------------" << endl;				// seperator
	derived_object.Base::method();	     // OK. method() of Base is public

	cout << "----------------" << endl;				// seperator
	derived_object.Base::method(5);	 // OK. method() of Base is public
	
	cout << "----------------" << endl;				// seperator
	derived_object.notRedefined();		 // OK. Not Redefined
	
	return 0;
}