// point.cpp for e09_7b
// Methods of the Point class


#include <iostream>
using std::cout;
using std::endl;
#include "point.h"

// Constructor with two parameters to initialize x and y coordinates
Point::Point(int firstX, int firstY )
{
	cout << "Point Constructor is called..." << endl;
	// It can call its methods
	setX(firstX); // Accepts only valid values 
	setY(firstY); // Accepts only valid values 
}

// Virtual method
void Point::print() const {
	cout << "The coordinates of the Point: ";
	cout << "X = " << m_x << ", Y = " << m_y << endl;
}

// Setters
void Point::setX(int new_x) {
	if (new_x >= MIN_x) m_x = new_x;  // Accepts only valid values 
}
void Point::setY(int new_y) {
	if (new_y >= MIN_y) m_y = new_y;  // Accepts only valid values 
}

// Other methods if any .............