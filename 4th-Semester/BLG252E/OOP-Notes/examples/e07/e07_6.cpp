// e07_6.cpp
// Redefining the move function of the Point class under a private inheritance

#include <iostream>
using std::cout;
using std::endl;

// *** The Point Class (Base Class) has lower limits but not upper limits
class Point {								
public:
	Point() = default;						// Default Constructor
	void print() const;			            // Prints coordinates on the screen
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	void setX(int);
	void setY(int);
	bool move(int, int);					// A method to move points
	// Static public constants
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
private:
	int m_x{ MIN_x }, m_y{ MIN_y };				// x and y coordinates are private
};

// ***** Bodies of Member Functions of the Point class *****

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

// A function to move the points 
// If the values fall within the limits they are accepted, the point moves, and the function returns true.
// If the values are not within the limits, the point does not move, and the function returns false.
bool Point::move(int new_x, int new_y)
{		
	if (new_x >= MIN_x &&					// if new_x is within the limits
		new_y >= MIN_y)						// if new_x is within the limits
	{
		m_x = new_x;						// assigns new value to x coordinate
		m_y = new_y;						// assigns new value to y coordinate 
		return true;
	}
	return false;						// new values are not accepted
}

// Enumeration to define colors
enum class Color {Blue, Purple, Green, Red};  

// *** The ColoredPoint Class (Derived Class)
// A colored point has lower limits and upper limits
class ColoredPoint : private Point {					// Private inheritance
public:
	ColoredPoint (Color);								// Constructor to initialize the colored point
	Color getColor() const { return m_color; }			// Getter returns color of the point
	bool move(int, int);								// move of Point is redefined
	void print() const;					                // ColoredPoint redefines the print function
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
	// Static public constants
	// Upper Limits of x and y coordinates
	static inline const int MAX_x{100};					// MAX_x = 100 
	static inline const int MAX_y{200};					// MAX_y = 200
private:
	Color m_color;										// Color of the point
};

// ***** Bodies of Member Functions of the ColoredPoint class *****
// Constructor 
ColoredPoint::ColoredPoint(Color in_color) : m_color{in_color}
{
	cout << "Constructor of the ColoredPoint is called..." << endl;
}

// The move functioin of the Point class is overriden
// The Coloredpoint has also upper limits
bool ColoredPoint::move(int new_x, int new_y)
{
	if (new_x <= MAX_x && new_y <= MAX_y)		// if new_x and new_y are within the limits
		return Point::move(new_x, new_y);  // calls the move of Point
	return false;									  // new values are not accepted
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
	ColoredPoint colored_point1{ Color::Green };		// A green point
	if (colored_point1.move(200, 2000))		    // move of ColoredPoint
		cout << "Coordinates are accepted" << endl;
	else
		cout << "Coordinates are NOT accepted" << endl;
	colored_point1.print();								// print of ColoredPoint

	cout << "----------------" << endl;				// seperator
	if (colored_point1.move(50, 60))			// move of ColoredPoint
		cout << "Coordinates are accepted" << endl;
	else
		cout << "Coordinates are NOT accepted" << endl;
	colored_point1.print();								// print of ColoredPoint
	
	// colored_point1.Point::move(200, 200);			// Error! Point is a private base
	// colored_point1.setX(100);						// Error! Point is a private base
	// colored_point1.Point::print();					// Error! Point is a private base
	return 0;
}