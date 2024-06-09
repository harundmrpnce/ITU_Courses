// e07_12a.cpp
// The default copy constructor under Inheritance

#include <iostream>
using std::cout;
using std::endl;


// *** The Point Class (Base Class) does not have a programmer-defined copy constructor
class Point {								
public:
	Point() { cout << "Default Constructor of the Point " << endl; }
	Point(int, int);						// Constructor with two integers to initialize x and y coordinates
	void print() const;			            // Prints coordinates on the screen
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	void setX(int);
	void setY(int);
	// Static public constants
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
private:
	int m_x{ MIN_x }, m_y{ MIN_y };				// x and y coordinates are private
};

// ***** Bodies of Member Functions of the Point class *****

// Constructor to initialize x and y coordinates
Point::Point(int in_x, int in_y)
{
	cout << "Constructor of the Point with two parameters..." << endl;
	// It can call its methods
	setX(in_x); // Accepts only valid values 
	setY(in_y); // Accepts only valid values 
}

// A const method to print the coordinates on the screen
void Point::print() const
{
	cout << "X= " << m_x << ", Y= " << m_y << endl;
}

// Setters
void Point::setX(int new_x) {
	if (new_x >= MIN_x) m_x = new_x;  // Accepts only valid values 
}
void Point::setY(int new_y) {
	if (new_y >= MIN_y) m_y = new_y;  // Accepts only valid values 
}

// Enumeration to define colors
enum class Color {Blue, Purple, Green, Red};  

// *** The ColoredPoint Class (Derived Class)
// Derived class does not have a programmer-defined copy constructor
class ColoredPoint : public Point {						// Public inheritance
public:
	ColoredPoint(int, int, Color);
	Color getColor() const { return m_color; }			// Getter returns color of the point
	void print() const;					                // ColoredPoint redefines the print function
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
private:
	Color m_color{Color::Red};										// Color of the point
};

ColoredPoint::ColoredPoint(int in_x, int in_y, Color in_color) : Point{ in_x,in_y }, m_color{ in_color }
{
	cout << "ColoredPoint Constructor" << endl;
}

// ColoredPoint redefines the print function of the Point
// This function prints the color as well
void ColoredPoint::print() const
{
	Point::print();       // calls print inherited from Point to print x and y coordinates
	// prints the color
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
// -------- Main Program -------------
int main()
{
	ColoredPoint colored_point1{ 10, 20, Color::Blue};				// Constructor of the ColoredPoint
	colored_point1.print();	
	cout << "----------------" << endl;								// seperator

	ColoredPoint colored_point2{colored_point1};					// Default copy constructors are invoked
	// colored_point2 is a copy of colored_point1
	colored_point2.print();

	return 0;
}