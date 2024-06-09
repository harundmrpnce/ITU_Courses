// e07_18.cpp
// References to objects and inheritance

#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

// *** The Point Class (Base Class)
class Point {				
public:
	Point(int, int);						// Constructor to initialize coordinates 
	// Getters are const:
	int getX() const { return m_x; }         // Accessor for x coordinate
	int getY() const { return m_y; }         // Accessor for y coordinate
	// Setters
	void setX(int);
	void setY(int);
	// Lower Limits of x and y coordinates
	static inline const int MIN_x{};            // Zero initialization
	static inline const int MIN_y{};
private:
	int m_x{ MIN_x }, m_y{ MIN_y };			   // x and y coordinates are initialized 
};

// ***** Methods of the Point class *****

// Constructor with two parameters to initialize x and y coordinates
Point::Point(int firstX, int firstY )
{
	// It can call its methods
	setX(firstX); // Accepts only valid values 
	setY(firstY); // Accepts only valid values 
}

// Setters
void Point::setX(int new_x) {
	if (new_x >= MIN_x) m_x = new_x;  // Accepts only valid values 
}
void Point::setY(int new_y) {
	if (new_y >= MIN_y) m_y = new_y;  // Accepts only valid values 
}

// Enumeration to define colors
enum class Color { Blue, Purple, Green, Red };

// *** The ColoredPoint Class (Derived Class)
class ColoredPoint : public Point {						// Public inheritance
public:
	ColoredPoint(int, int, Color);
	Color getColor() const { return m_color; }			// Getter returns color of the point
	void setColor(Color in_color) { m_color = in_color; }// Setter modifies the color of the point
private:
	Color m_color{ Color::Red };										// Color of the point
};

ColoredPoint::ColoredPoint(int in_x, int in_y, Color in_color) : Point{ in_x,in_y }, m_color{ in_color }
{}

// *** A class that contains Point-related tools 
class GraphicTools {
public:
	double distanceFromZero(const Point&) const;	//calculates and returns the distance of a point from(0, 0)
};

// Calculates and returns the distance of a point from(0, 0)
// Parameter type is a reference to Point objects
// This function can also get a reference to ColoredPoint objects
double GraphicTools::distanceFromZero(const Point& in_point) const {
	double local_x = in_point.getX();					
	double local_y = in_point.getY();
	return sqrt(local_x * local_x + local_y * local_y);   // distance from (0,0)
}

// -------- Main Program -------------
int main()
{
	GraphicTools gTool;						// A GraphicTools object
	
	Point point1{ 10, 20 };					// A Point object
	cout << "Distance of the point1 from Zero is " << gTool.distanceFromZero(point1) << endl;  // Parameter is a referance to a Point object

	ColoredPoint col_point1{ 30, 40, Color::Blue };					// A ColoredPoint object
	cout << "Distance of the col_point1 from Zero is " << gTool.distanceFromZero(col_point1) << endl;  // Parameter is a referance to a ColoredPoint object
	return 0;
}