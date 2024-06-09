// e07_4a.cpp
// Private Inheritance
// Redefining Access Specifications

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// *** The Point Class (Base Class) has lower limits but not upper limits
class Point {								
public:
	Point() = default;						// Default Constructor
	void print() const;			            // const method prints coordinates on the screen
	// Getters are const:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	// Setters are NOT const:
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
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
	void setAll(int, int, Color);						// Set all attributes
	using Point::print;									// print() of Point is public again	
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

// Set all attributes
// The derived class checks the upper limit values
void ColoredPoint::setAll(int in_x, int in_y, Color in_color) {
	if (in_x <= MAX_x) setX(in_x);
	if (in_y <= MAX_y) setY(in_y);
	m_color = in_color;
}

// -------- Main Program -------------
int main()
{
	ColoredPoint colored_point1{ Color::Green };		// A green point
	// Argumens beyond the lower and upper limits are not accepted
	colored_point1.setAll(200, 200, Color::Red);	 // Upper limits!
	colored_point1.setAll(-10, -20, Color::Red);	 // Lower limits!
	
	//colored_point1.move(200, 200);					// Error! move() from Point is private
	//colored_point1.setX(500);							// Error! setX() from Point is private
	
	colored_point1.print();								// OK!print function of Point is public again
	return 0;
}