// e02_3.cpp
// Overloading of function names

#include <iostream>			// Prior to C++20 header file for input and output
// import <iostream>;            // Since C++20
// import std;                      // Since C++23
using std::cout;
using std::endl;

struct ComplexT{        // Structure for complex numbers
    float re,im;
};

void print (float value){   // print function for real numbers
   cout << "print function for real numbers" << endl;
   cout << "value= " << value << endl;
}
void print (ComplexT c){    // print function for complex numbers
   cout << "print function for complex numbers" << endl;
   cout << "real= " << c.re << " im= " << c.im << endl;
}
void print (float value, char c){    // print function for real numbers and chars
   cout << "print function for real numbers and chars" << endl;
   cout << "value= " << value << " c= " << c << endl;
}
//--------- Main Function ----------
int main()
{
	ComplexT z;			// A complex number is defined
	z.re=0.5f;			// Fields of the complex number are filled with float values
	z.im=1.2f;			 
	print(z);			         // print for complex number
	print(4.2f);			 // print for real number (float)
	print(2.5,'A');	     // print for real number and char
	return 0;
}
