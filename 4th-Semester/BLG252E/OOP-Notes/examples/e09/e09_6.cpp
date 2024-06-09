// e09_6.cpp
// Abbreviated Function Templates 
// The auto keyword as a placeholder for function parameter types

#include <iostream>
using std::cout;
using std::endl;

// Abbreviated Function Template
// The function sums two arguments

auto sumOf(const auto& n1, const auto& n2)
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
