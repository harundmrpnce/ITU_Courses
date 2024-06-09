// e04_16.cpp
//	Static Methods
// Static methods can access static data memebers without an object
// We use a static counter to count how many objects of the Point class exist. 

#include <iostream>
using std::cout;
using std::endl;

class Point {				         // Declaration of the Point Class with low-limits
public:
	// Static constants
	// Lower Limits of x and y coordinates for all objects
	static inline const int MIN_x{ };   // Same for all objects of Point
	static inline const int MIN_y{ };   // Same for all objects of Point

private:
	static inline unsigned int s_point_count{};  // A static counter 

public:
	static void initPointCount(unsigned int);  // Static methods to set and read static data members
	static unsigned int getPointCount();

	Point();			           // Default Constructor
	Point(int, int);			   // Constructor to initialize x and y cooridinates
	Point(const Point&);			// Copy Constructor
	void print() const;			            // const method prints coordinates on the screen
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	void setX(int);
	void setY(int);
	bool move(int, int);					// A non-constant method to move points
	~Point();								// Destructor
private:
	int m_x{ MIN_x }, m_y{ MIN_y };	  // x and y coordinates are initialized 
};

// ***** Bodies of Member Functions *****

// A static method to set the stataic data member s_point_count
void Point::initPointCount(unsigned int in_count) {
	s_point_count = in_count;
}

// A static method to read the stataic data member s_point_count
unsigned int Point::getPointCount() {
	return s_point_count;
}

// The default Constructor
// We write the default constructor only to monitor how many objects are created
Point::Point() {
	cout << "Default Constructor is called..." << endl;
	s_point_count++;					// increments the static counter
	cout << "Number of objects= " << s_point_count << endl;
}

// Constructor to initialize x and y coordinates
Point::Point(int in_x, int in_y)
{
	cout << "Constructor is called..." << endl;
	// It can call its methods
	setX(in_x); // Accepts only valid values 
	setY(in_y); // Accepts only valid values 
	s_point_count++;					// increments the static counter
	cout << "Number of objects= " << s_point_count << endl;
}

// Copy Constructor
Point::Point(const Point& in_point)
{
	cout << "The Copy Constructor is called..." << endl;
	setX(in_point.m_x); // Accepts only valid values 
	setY(in_point.m_y); // Accepts only valid values 
	s_point_count++;					// increments the static counter
	cout << "Number of objects= " << s_point_count << endl;
}

// A const method to print the coordinates on the screen
void Point::print() const
{
	cout << "X= " << m_x << "Y= " << m_y << endl;
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

// Destructor
// A user-defined destructor is NOT necessary for the Point class
// We write it only to monitor how many objects are created and destructed
Point::~Point() {
	cout << "Destructor is called..." << endl;
	s_point_count--;					// decrements the static counter
	cout << "Number of objects= " << s_point_count << endl;
}
// -------- Main Program -------------
int main()
{
	// we haven't created any object yet.
	Point::initPointCount(100);			// Counter intialized to 100 for all objects.

	cout << "  Entering 1. BLOCK............" << endl;
	Point point1{ 10,20 }, point2{ 30,40 };				// Two objects are created
	Point point3;										// One object is created
	{
		cout << "  Entering 2. BLOCK............" << endl;
		Point point4{}, point5{ 100,200 };				// Two inner objects are created
		cout << "  Exiting 2. BLOCK............" << endl;
	}
	cout << "  Exiting 1. BLOCK............" << endl;
	return 0;
}