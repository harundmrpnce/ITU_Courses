// e02_4.cpp
//Return by reference

#include <iostream>			// Prior to C++20 header file for input and output
// import <iostream>;            // Since C++20
// import std;                      // Since C++23

// max  function returns a refference to the largest element of an array
int&  max(int a[], unsigned int length)			
{
	unsigned int i{};    							// i is indices of the largest element
   for (unsigned int j=0 ; j<length ; j++)			// Find the largest element of a[]
	   if (a[j] > a[i])  i = j;
   return a[i];		// returns refference to a[i]
}

int main()
{
   int array[] = {12, -54 , 1 , 123, 63};				// An aray with 5 elements
   max(array,5) = 0;								// Write 0 on the largest element
   for(unsigned int i=0; i<5; i++) std::cout << array[i] << " ";       // array on the screen
   return 0;
}

