// e07_15.cpp
// Multiple Inheritance 
#include<iostream>
using std::cout;
using std::endl;

class Base1{        // Base 1
 public:
   Base1(){ cout << "Base1 default constructor" << endl; }
   ~Base1() { cout << "Base1 destructor" << endl; }
   void f1(){cout << "Base1 f1" << endl;}
   void f2(){cout << "Base1 f2" << endl;}
   void f3() { cout << "Base1 f3" << endl; }
   void f4() { cout << "Base1 f4" << endl; }                   // Not redefined
};

class Base2{      // Base 2
 public:
   Base2() { cout << "Base2 default constructor" << endl; }
   ~Base2() { cout << "Base2 destructor" << endl; }
   void f1() { cout << "Base1 f2" << endl; }
   void f2(int){cout << "Base2 f2" << endl;}
   void f3(int) { cout << "Base1 f3" << endl; }
};

// ** Derived is derived from Base1 and Base2 **
class Derived : public Base1 , public Base2{
 public:
	Derived() { cout << "Derived default constructor" << endl; }
	~Derived() { cout << "Derived destructor" << endl; }
	void f1(){cout << "Derived f1" << endl;}				// Redefines Base1, Base2 f1() methods with the same signature
	void f2(int, char) { cout << "Derived f2" << endl; }    // Redefines Base1, Base2 f2(...) methods with differenet signatures
	void f5() {												// Calls Base1 and Base2 methods
		cout << "Derived f5 calls Base functions" << endl;
		f1();												// Derived::f1();
		Base1::f1();
		Base2::f1();
		//f2();												// Error! f2 is redefined in Derived. It takes two arguments
		//f3(3);											// Derived::f3 is ambiguous. It is not overloading!!
		Base2::f3(3);										// OK	
		f4();												// OK! Base1::f4 is not redefined
	}
};

int main()
{
	Derived d;						// Default constructors
	d.f1();							// Derived::f1
	d.Base1::f1();					// Base1::f1
	d.f2(1, 'A');					// Derived::f2
	//d.f2(1);					    // Error! Derived::f2 takes two arguments
	d.Base2::f2(1);					// Base2::f2
	//d.f3();						// Error! Derived f3 is ambiguous. This is not overloading!
	d.f4();							// Base1::f4. It is not redefined
	d.f5();							// Derived::f5
	
	return 0;
}
