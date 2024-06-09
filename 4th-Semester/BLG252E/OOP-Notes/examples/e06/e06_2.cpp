// e06_2.cpp
// Compositon
// A triangle is composed of three Point objects
// Point class does not contain a default constructor

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

// Declaration of the Point Class with low-limits
// This class does not contain a default constructor
class Point {								
public:
	Point(int, int);						// Constructor to initialize x and y coordinates
	Point(const Point&);					// Copy Constructor
	void print() const;			            // const method prints coordinates on the screen
	double operator-(const Point&) const;	// Calculates the distance between two points (using operator overloading)
	double getDistance(const Point&) const;	// Calculates the distance between two points (without operator overloading)
	// Getters:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	// Setters:
	void setX(int);
	void setY(int);
	~Point();								// Destructor, not necessary
	// Static public constants
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
private:
	int m_x{ MIN_x }, m_y{ MIN_y };				// x and y coordinates are initialized 
};

// ***** Bodies of Member Functions of the Point class *****

// Constructor to initialize x and y coordinates
Point::Point(int in_x, int in_y)
{
	cout << "Constructor of the Point is called..." << endl;
	// It can call its methods
	setX(in_x); // Accepts only valid values 
	setY(in_y); // Accepts only valid values 
}

// Copy Constructor
Point::Point(const Point& in_point)
{
	cout << "The Copy constructor of the Point is called..." << endl;
	setX(in_point.m_x); // Accepts only valid values 
	setY(in_point.m_y); // Accepts only valid values 
}

// A const method for the operator - calculates and returns the distance between two points (operator overloading)
double Point::operator-(const Point& in_point) const {
	return std::sqrt(std::pow((m_x- in_point.m_x),2) + std::pow((m_y - in_point.m_y),2));   // distance
}

// A const method for that calculates and returns the distance between two points (without operator overloading)
double Point::getDistance(const Point& in_point) const {
	return std::sqrt(std::pow((m_x - in_point.m_x), 2) + std::pow((m_y - in_point.m_y), 2));   // distance
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

// Destructor for the Point class is not necessary
// We write this method to see when the objects are destroyed
Point::~Point()
{
	cout << "Destructor the Point is called..." << endl;
}

// Triangle is composed of three Point objects
class Triangle {
public:
	Triangle(const Point&, const Point&, const Point&);			// Constructor with three points
	Triangle(int, int, int, int, int, int);						// Constructor with the coordinates of three corners
	double getPerimeter()const;									// Calculates and returns the perimeter of the triangle
	void print()const;											// Print the corners
	~Triangle();												// Destructor, not necessary	
private:
	Point m_corner1, m_corner2, m_corner3;						// Corners of the triangle
};

// ***** Bodies of Member Functions of the Triangle class *****

// Constructor with three points
Triangle::Triangle(const Point& in_corner1, const Point& in_corner2, const Point& in_corner3)
	:m_corner1{ in_corner1 }, m_corner2{ in_corner2 }, m_corner3{ in_corner3 }
{
		cout << "Constructor of the Triangle with three points is called..." << endl;
}

// Constructor with the coordinates of three corners
Triangle::Triangle(int corner1_x, int corner1_y, int corner2_x, int corner2_y, int corner3_x, int corner3_y)
	:m_corner1{ corner1_x,corner1_y }, m_corner2{ corner2_x,corner2_y }, m_corner3{ corner3_x,corner3_y }
{
	cout << "Constructor of the Triangle with the coordinates is called..." << endl;
}

// Calculates and returns the perimeter of the triangle
double Triangle::getPerimeter()const {
	
	return (m_corner1 - m_corner2) + (m_corner2 - m_corner3) + (m_corner3 - m_corner1);
	//return m_corner1.getDistance(m_corner2) + m_corner2.getDistance(m_corner3) + m_corner3.getDistance(m_corner1); // without operator overloading
}

// Print the corners
void Triangle::print()const {
	cout << "Corners of the triangle:" << endl;
	m_corner1.print();
	m_corner2.print();
	m_corner3.print();
}

// Destructor for the Triangle class is not necessary
// We write this method to see when the objects are destroyed
Triangle::~Triangle()
{
	cout << "Destructor the Triangle is called..." << endl;
}

// -------- Main Program -------------
int main()
{
	Triangle triangle1{10, 20, 30, 40, 50, 60};		// Coordiantes of the corners are given
	triangle1.print();
	cout << "Perimeter of the triangle1 = " << triangle1.getPerimeter() << endl;
	
	cout << "----------------------" << endl; // Seperator
	Point point1{0, 20};       // 1. point object
	Point point2{10, 20};	   // 2. point object
	Point point3{30, 40 };	   // 3. point object
	Triangle triangle2{ point1, point2, point3 };	// Point objects are given
	triangle2.print();
	cout << "Perimeter of the triangle2 = " << triangle2.getPerimeter() << endl;

	cout << "----------------------" << endl; // Seperator
	return 0;
}