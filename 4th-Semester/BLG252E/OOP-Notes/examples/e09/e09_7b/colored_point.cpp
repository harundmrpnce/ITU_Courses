// colored_point.cpp for e07_19
// Methods of the ColoredPoint class

#include <iostream>
using std::cout;
using std::endl;
#include "colored_point.h"

ColoredPoint::ColoredPoint(int in_x, int in_y, Color in_color) : Point{ in_x,in_y }, m_color{ in_color }
{
	cout << "ColoredPoint Constructor" << endl;
}

// Virtual method
void ColoredPoint::print() const {
	Point::print();
	cout << "The color: ";
	switch (m_color)
	{
	case Color::Blue: cout << "Color = Blue" << endl;
		break;
	case Color::Purple: cout << "Color = Purple" << endl;
		break;
	case Color::Green: cout << "Color = Green" << endl;
		break;
	case Color::Red:  cout << "Color = Red" << endl;
		break;
	default: cout << "Not a standard color" << endl;
		break;
	}
}

// Other methods if any .............