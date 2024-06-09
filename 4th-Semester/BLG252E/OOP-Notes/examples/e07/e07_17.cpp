// e07_17.cpp
// Pointer to objects under Inheritance

#include <iostream>
using std::cout;
using std::endl;


// *** The Point Class (Base Class) 
class Point {								
public:
	Point() { cout << "Default Constructor of the Point " << endl; }
	Point(int, int);						// Constructor with two integers to initialize x and y coordinates
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	void setX(int);
	void setY(int);
	bool move(int, int);					// A non-constant method to move points
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
class ColoredPoint : public Point {						// Public inheritance
public:
	ColoredPoint(int, int, Color);
	Color getColor() const { return m_color; }			// Getter returns color of the point
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
private:
	Color m_color{Color::Red};										// Color of the point
};

ColoredPoint::ColoredPoint(int in_x, int in_y, Color in_color) : Point{ in_x,in_y }, m_color{ in_color }
{
	cout << "ColoredPoint Constructor" << endl;
}

// -------- Main Program -------------
int main()
{
	ColoredPoint  objColoredPoint{ 10, 20, Color::Blue };	// Object of ColoredPoint type
	Point* ptrPoint = &objColoredPoint;						// Pointer to Point points to ColoredPoint 
	ptrPoint->move(30, 40);						// OK. Moving is a Point-behavior
	//ptrPoint->setColor(Color::Green);						// ERROR! Setting the color is not a Point-behavior. 
	cout << "X = " << ptrPoint->getX() << endl;				// OK. 
	cout << "----------------" << endl;				// seperator

	ColoredPoint* ptrColoredPoint = &objColoredPoint;		// Pointer to ColoredPoint points to ColoredPoint 
	ptrColoredPoint->move(100, 200);				// OK. ColoredPoint is a Point
	ptrColoredPoint->setColor(Color::Green);			// OK. ColoredPoints behavior
	return 0;
}