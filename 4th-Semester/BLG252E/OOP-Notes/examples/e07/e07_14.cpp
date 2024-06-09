// e07_14.cpp
// Inheriting from the library
// Creating a colored string

#include <iostream>         // for IO operations 
#include <string>			// Standard string
using std::cout;
using std::endl;

// Enumeration to define colors
enum class Color { Blue, Purple, Green, Red };

// A class to define colored strings is derived from std::string
class ColoredString : public std::string {
public:
  ColoredString() = default;				             // Default constructor 
  ColoredString(const char*, Color);				     // Constructor to initialize the colored string
  void print() const;										// A member function to print the colored string
  Color getColor() { return m_color; }const					// Getter returns color of the point
  void setColor(Color in_color) { m_color = in_color; }		// Setter modifies the color of the string
private:
	Color m_color{Color::Red};											// Color of the string
};

// Constructor
ColoredString::ColoredString(const char* inData, Color in_color)
	:std::string{ inData }, m_color{ in_color }
{}

void ColoredString::print() const
{
	cout << *this << endl;
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
	default:
		break;
	}
}

int main()
{
	ColoredString firstString{ "First String", Color::Blue };				// Constructor is called
	ColoredString secondString{ firstString };								// Copy constructor is invoked
	firstString.print();										
	secondString.print();
	cout << "-------------------" << endl;
	
	ColoredString thirdString{ "Third String", Color::Green };			    // Constructor is invoked									
	
	secondString += thirdString;											// += operator of std::strig
	secondString.print();													// "First StringThird String"
	cout << "-------------------" << endl;

	secondString.insert(12, "-");									// Insert "-" to the position 12
	secondString.print();													// "First String-Third String"
	cout << "-------------------" << endl;

	ColoredString fourthString;												// Default constructor is invoked
	fourthString = secondString;											// Assignment operators
	fourthString.print();
	
	return 0;
}