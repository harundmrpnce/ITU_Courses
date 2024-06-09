// e10_3.cpp
// Smart Pointers
// weak_ptr<T>

#include <memory>		// For smart pointers
#include <iostream>
using std::cout;
using std::endl;

class AnyClass {
public:
	AnyClass() { cout << "Constructor of AnyClass" << endl; }; // Only to see that it runs
	~AnyClass() { cout << "Destructor of AnyClass" << endl; }  // Only to see that it runs
	void print() const { cout << "Print of AnyClass" << endl; }
};

// -------- Main Program -------------
int main()
{
	std::weak_ptr<AnyClass> smart_ptr1;
	cout << smart_ptr1.use_count() << endl;	
	{	// A new scope
		std::shared_ptr<AnyClass> smart_ptr2 {std::make_shared<AnyClass>()}; 
		smart_ptr1 = smart_ptr2;		// weak_ptr points to shared_ptr
		cout << "The Number of sharing pointers =" << smart_ptr1.use_count() << endl;	// Number of pointers sharing the same object. weak_ptr does not count
		cout << "----------------------" << endl;     // Seperator
		
		std::shared_ptr<AnyClass> smart_ptr3;      // Another shared pointer. An object is not created
		smart_ptr3 = smart_ptr2;
		cout << "The Number of sharing pointers =" << smart_ptr1.use_count() << endl;	// Number of pointers sharing the same object. weak_ptr does not count
		
		cout << "End of the scope" << endl;
	} // End of scope. The object will be deleted.

	// The object pointed to smart_ptr1 does not exist.
	// smart_ptr1 still exists.
	cout << "The Number of sharing pointers =" << smart_ptr1.use_count() << endl;	// Number of pointers sharing the same object. weak_ptr does not count
	return 0;
}