// e09_3.cpp
// The function template to calculate the absolute value of a number

#include <iostream>
using std::cout;
using std::endl;

// function returns the index number of an item, or -1 if it is not found in the array
template <typename T>
int find(const T* array, T value, unsigned int size)
{
    for (unsigned int j = 0; j < size; j++)
        if (array[j] == value) return j;
    return -1;
}

int main()
{
    char charArr[] { 'a', 'c', 'f', 's', 'u', 'x', 'z'};    	  // array 
    char ch{ 'f' };			 	                                 // value to find 
    int intArr[] { 1, 3, 5, 9, 11, 13 };
    int in{ 6 };
    double doubleArr[] { 1.0, 3.0, 5.0, 9.0, 11.0  };
    double db{ 3.0 };

    cout << ch << " in charArray : index = " << find(charArr, ch, 7) << endl;
    cout << in << " in intArray: index= " << find(intArr, in, 6) << endl;
    cout << db << " in doubleArray: index= " << find(doubleArr, db, 5) << endl;

    /* Template Arguments Must Match
    int intArray[] { 1, 3, 5, 7 };             // int array 
    float f1{ 5.0 };                           // float value 
    int value = find(intArray, f1, 4);         // ERROR!  find(int*, float, int); arguments do not match
    */

    return 0;
}