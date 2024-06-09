// e04_15.cpp
//	Static Constant Data Members

#include <iostream>
using std::cout;
using std::endl;

class Point{				         // Declaration of the Point Class with low-limits
public:
	// Static constants
	// Lower Limits of x and y coordinates for all objects
	static inline const int MIN_x{10};   // Same for all objects of Point
	static inline const int MIN_y{20};   // Same for all objects of Point

	Point() = default;					// Default constructor with an empty body
	Point(int, int);					// Constructor
	void print() const;			            // const method prints coordinates on the screen
	// Getters are const:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	// Setters are NOT const:
	void setX(int);
	void setY(int);
	bool move(int, int);					// A non-constant method to move points
private:
	int m_x{ MIN_x }, m_y{ MIN_y };	  // x and y coordinates are initialized 
};

// ***** Bodies of Member Functions *****

Point::Point(int newX, int newY)					// Constructor
{
	setX(newX);
	setY(newY);
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

// A function to move the points 
// It checks the input values.
// If the values fall within the limits they are accepted, the point moves, and the function returns true.
// If the values are not within the limits, the point does not move, and the function returns false.
bool Point::move(int new_x, int new_y)
{
	if (new_x >= MIN_x &&  // if new_x is within the limits
		new_y >= MIN_y)    // if new_x is within the limits
	{
		m_x = new_x;						// assigns new value to x coordinate
		m_y = new_y;						// assigns new value to y coordinate 
		return true;
	}
	return false;						// new values are not accepted
}

// -------- Main Program -------------
int main()
{
	// We have not created an object yet
	// We chack the values entered by the user. 
	// The values cannot be less than the minimum values
	int in_x;
	do {
		cout << "Enter the x coordinate. It must be greater than " << Point::MIN_x << endl;
		std::cin >> in_x;
	} while (in_x < Point::MIN_x);
	int in_y;
	do {
		cout << "Enter the y coordinate. It must be greater than " << Point::MIN_y << endl;
		std::cin >> in_y;
	} while (in_y < Point::MIN_y);

	Point point1;
	point1.move(in_x, in_y);
	point1.print();

	cout << "----------------------" << endl; // Seperator
	Point point2(Point::MIN_x, Point::MIN_y);  // we can call the constructor using the limits
	point2.print();

	return 0;
}