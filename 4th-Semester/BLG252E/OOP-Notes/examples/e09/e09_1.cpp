// e09_1.cpp
// The function template to calculate the absolute value of a number

#include <iostream>
using std::cout;
using std::endl;

template <typename T>      // function template, template <class T> is also valid
T abs(T n)
{
	return n < 0 ? -n : n;
}

int main()
{ 
	short int short_int1{ 500 };
	short int short_int2{ -600 };
    long long int  long_long_int1{ 123456789012345 };
    long long int  long_long_int2{ -9876543210987654 };
    double double1{ 9.95 };
    double double2{ -10.15 };
  // calls instantiate functions
  cout << "abs(" << short_int1 << ") = " << abs(short_int1) << endl;                     // abs(short int) 
  cout << "abs(" << short_int2 << ") = " << abs(short_int2) << endl;                     // abs(short int) 
  cout << "abs(" << long_long_int1 << ") = " << abs(long_long_int1) << endl;          // abs(long long int)
  cout << "abs(" << long_long_int2 << ") = " << abs(long_long_int2) << endl;          // abs(long long int)
  cout << "abs(" << double1 << ") = " << abs(double1) << endl;                       // abs(double) 
  cout << "abs(" << double2 << ") = " << abs(double2) << endl;                       // abs(double)  
  return 0;
} 
