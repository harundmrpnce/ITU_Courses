// e10_1b.cpp
// Smart Pointers
// unique_ptr<T>
// There can never be two or more unique_ptr<T> objects simultaneously pointing to the same memory address.



#include <memory>		// For smart pointers
#include <iostream>
using std::cout;
using std::endl;

class AnyClass {								
public:
	AnyClass() { cout << "Constructor of AnyClass" << endl; }; // Only to see that it runs
	~AnyClass() { cout << "Destructor of AnyClass" << endl; }  // Only to see that it runs
};

// -------- Main Program -------------
int main()
{
	AnyClass* ptr { new AnyClass() };  // Error. You cannot create a copy of a unique_ptr
	std::unique_ptr<AnyClass> smart_ptr1{ ptr };
	
	// std::unique_ptr<AnyClass> smart_ptr2;					  // A unique_ptr without initialization
	// smart_ptr2 = smart_ptr1;  // Error. You cannot create a copy of a unique_ptr
	
	// We do not need to release memory manually using the delete operator.
	cout << "End of the program" << endl;
	return 0;
}