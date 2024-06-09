// main.cpp for e09_7b

#include <iostream>
using std::cout;
using std::endl;

#include "colored_point.h"
#include "stack.h"


// -------- Main Program -------------
int main()
{
	
	Stack<const Point *> s_pointPtr;						// s_pointPtr is an object of the class Stack<const Point *>  
	
	ColoredPoint  col_point1{ 10, 20, Color::Blue };	    // Object of ColoredPoint type
	s_pointPtr.push(&col_point1);							// Push a colored point into the stack

	Point *ptrPoint1 = new Point {30, 40};						// Dynamic Point object 
	s_pointPtr.push(ptrPoint1);							        // Push a point into the stack

	ColoredPoint  *ptrColPoint1 = new ColoredPoint{ 50, 60, Color::Red };	    // Dynamic Object of ColoredPoint type
	s_pointPtr.push(ptrColPoint1);			                 // Push a colored point into the list

	cout << "Points in the stack:" << endl;
	s_pointPtr.pop()->print();										// pop and call the print()
	s_pointPtr.pop()->print();										// pop and call the print()
	s_pointPtr.pop()->print();										// pop and call the print()

	delete ptrPoint1;
	delete ptrColPoint1;
	
	return 0;
}
