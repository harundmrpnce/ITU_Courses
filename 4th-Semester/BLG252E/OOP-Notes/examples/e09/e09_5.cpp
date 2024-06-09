// e09_5.cpp
// Return Type Deduction in Templates

#include <iostream>
using std::cout;
using std::endl;

// template function 
// The function sums two arguments
template <typename T1, typename T2> 
auto sumOf(const T1& n1, const T2& n2)
{ 
    return n1 + n2;
} 

int main()
{
    int i1{ 5 }, i2{ -7 };
    double d1{ 3.05 }, d2{ -18.42 };
    
    cout << "Sum of i1 and i2 = " << sumOf(i1, i2) << endl;
    cout << "Sum of i1 and d1 = " << sumOf(i1, d1) << endl;
    cout << "Sum of d1 and d2 = " << sumOf(d1, d2) << endl;
    
	return 0;
}
