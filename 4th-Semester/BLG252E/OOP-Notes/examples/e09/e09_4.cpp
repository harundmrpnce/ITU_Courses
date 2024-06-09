// e09_4.cpp
// Multiple Template Arguments

#include <iostream>
using std::cout;
using std::endl;

// The type of the size of the array is a template type
template <typename T1, typename T2>
T2 find(const T1* array, T1 value, T2 size)
{
    for (T2 j = 0; j < size; j++)  			// note use of T2 
        if (array[j] == value) return j;
    return -1;
    // return static_cast<T2>(-1);  // we can add an explicit cast to T2 to silence any warnings about implicit conversions.
}


int main()
{
    short int short_index;
    const short int short_size{ 7 };
    char chrArray[short_size] { 'a', 'c', 'f', 's', 'u', 'x', 'z'};    	  // array 
    char ch{ 'f' };			 // value to find 

    short_index = find(chrArray, ch, short_size);
    cout << ch << " in chrArray : index = " << short_index << endl;
    
    long int long_index;
    const long int long_size{ 1234 };
    double doubleArr[long_size] { 1.0, 3.0, 5.0, 9.0, 11.0  };
    double db{ 4.2345 };
        
    long_index = find(doubleArr, db, long_size);
    cout << db << " in doubleArray: index= " << long_index << endl;
    return 0;
}