// e07_9b.cpp
// The constructor of the derived class calls the constructors of the base class
// In this example the Point class has three constructors

#include <iostream>
using std::cout;
using std::endl;

// *** The Point Class (Base Class)
// This class contains three constructors
class Point {								
public:
	Point();								// Default constructor
	Point(int);						        // Constructor assigns same value to x and y 
	Point(int, int);						// Constructor to initialize x and y coordinates
	void print() const;			            // prints coordinates on the screen
	// Getters are const:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	// Setters are NOT const:
	void setX(int);
	void setY(int);
	// Static public constants
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
private:
	int m_x{MIN_x}, m_y{MIN_y};						 // x and y coordinates are initialized 
};

// ***** Bodies of Member Functions of the Point class *****

// Default Constructor
// Actually it is not necessary. We use it only to put a mesage on the screen
Point::Point()
{
	cout << "Default Constructor of the Point (Base)" << endl;
	m_x = MIN_x;						// assigns minimum value to x coordinate
	m_y = MIN_y;						// assigns minimum value to y coordinate 
}
// Constructor assigns same value to x and y 
Point::Point(int in)
{
	cout << "Constructor (int) of the Point (Base)" << endl;
	if (in >= MIN_x &&  in >= MIN_y)    // if in is within the limits
	{
		m_x = in;						// assigns new value to x coordinate
		m_y = in;						// assigns new value to y coordinate 
	}
}
// Constructor to initialize x and y coordinates
Point::Point(int in_x, int in_y)
{
	cout << "Constructor (int, int) of the Point (Base)" << endl;
	if (in_x >= MIN_x &&  // if in_x is within the limits
		in_y >= MIN_y)    // if in_y is within the limits
	{
		m_x = in_x;						// assigns new value to x coordinate
		m_y = in_y;						// assigns new value to y coordinate 
	}
}

// A const method to print the coordinates on the screen
void Point::print() const
{
	std::cout << "X= " << m_x << ", Y= " << m_y << std::endl;
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
// This calss has three constructors
class ColoredPoint : public Point {
public:
	ColoredPoint();										// Default Constructor 
	ColoredPoint(Color);								// Constructor to initialize the colored point
	ColoredPoint (int, int, Color);						// Constructor to initialize the colored point
	void print() const;									// ColoredPoint redefines the print function
	Color getColor() const { return m_color; }			// Getter returns color of the point
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
private:
	Color m_color{ Color::Red };						// Color of the point
};

// ***** Bodies of Member Functions of the ColoredPoint class *****

// Default Constructor 
// It calls the default constructor of the Point
ColoredPoint::ColoredPoint() 
{
	cout << "Default constructor of the ColoredPoint (Derived)" << endl;
}

// Constructor with only the color
// It calls the constructor of the Point(int) 
ColoredPoint::ColoredPoint(Color in_color) : Point{1}, m_color { in_color }
{
	cout << "Constructor (Color) of the ColoredPoint (Derived)" << endl;
}

// Constructor with coordinates and color
// It calls the constructor (int, int) of the Point
ColoredPoint::ColoredPoint(int in_x, int in_y, Color in_color)
	: Point{in_x, in_y}, m_color{in_color}
{
	cout << "Constructor (int, int, Color) of the ColoredPoint (Derived)" << endl;
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
	ColoredPoint col_point1;							// A red point on (MIN_x, MIN_y)
	col_point1.print();									// print function of the ColoredPoint
	cout << "----------------" << endl;				// seperator

	ColoredPoint col_point2{Color::Purple };			// A purple point on (1,1)
	col_point2.print();									// print function of the ColoredPoint
	cout << "----------------" << endl;				// seperator

	ColoredPoint col_point3{10, 20, Color::Green };		// A green point on (10,20)
	col_point3.print();									// print function of the ColoredPoint
		
	return 0;
}