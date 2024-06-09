// e07_2.cpp
// Protected members

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// *** The Point Class (Base Class) has a procted member m_ID
class Point {								
public:
	Point() = default;						// Default Constructor
	void print() const;			            // const method prints coordinates on the screen
	// Getters are const:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	const string& getID() const { return m_ID; }         // Accessor for ID
	// Setters are NOT const:
	void setX(int);
	void setY(int);
	void setID(const string& in_ID) { m_ID = in_ID; }
	bool move(int, int);					// A non-constant method to move points
	// Static public constants
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
protected:
	string m_ID{"My ID"};						// Protected member
private:
	int m_x{MIN_x}, m_y{MIN_y};					// x and y coordinates are private 
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
class ColoredPoint : public Point {
public:
	ColoredPoint (Color);								// Constructor to initialize the colored point
	Color getColor() { return m_color; }const			// Getter returns color of the point
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
	void setAll(int, int, const string&,  Color);		// Set all attributes
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
// The derived class ColoredPoint can access the protected member of the Base directly
void ColoredPoint::setAll(int in_x, int in_y, const string& in_ID, Color in_color) {
	setX(in_x);			// calls method of the Base (Point)
	setY(in_y);			// calls method of the Base (Point)
	// m_x = in_x				// Error! m_x is private in Point
	m_ID = in_ID;				// access the protected member directly
	m_color = in_color;
}

// -------- Main Program -------------
int main()
{
	ColoredPoint col_point1{ Color::Green };		// A green point
	col_point1.setAll(10, 20, "Colored Point1", Color::Red);	// set all attributes of the colored point
	col_point1.print();								// print function is derived from base Point
	cout << "ID = " << col_point1.getID() << endl;
	return 0;
}