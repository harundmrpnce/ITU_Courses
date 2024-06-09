// e08_1c.cpp
// Polymorphism
// Calling a virtual function using a reference to base class Professor

#include <iostream>
#include <string>
using std::cout;
using std::endl;

//*** Base class: Professor
class Professor{      
public:
  Professor(const std::string&, const std::string&);  // Constructor: name, research area
  virtual void print() const;						  // virtual function
private:
  std::string m_name;
  std::string m_researchArea;
};

//** Bodies of the methods of the Professor
// Constructor
Professor::Professor(const std::string& in_name, const std::string& in_researchArea)
	                          : m_name{ in_name }, m_researchArea{ in_researchArea }
{}

void Professor::print() const       // virtual function
{
	cout << "Name: "<< m_name << endl;
	cout << "Research Area:"<< m_researchArea << endl;
}

//*** Derived class: Dean
class Dean : public Professor{  
public:
  Dean(const std::string&, const std::string&, const std::string&); // Constructor: name, research are, faculty name
  void print() const;
private:
	std::string m_facultyName;
};

//** Bodies of the methods of the Dean
// Constructor
Dean::Dean(const std::string& in_name, const std::string& in_researchArea, const std::string& in_facultyName)
	: Professor{ in_name, in_researchArea }, m_facultyName{ in_facultyName }
{}

void Dean::print() const     // virtual function
{
	Professor::print();
	cout << " I am the dean of " << m_facultyName << endl;
}

//*** User class: Rector
class Rector {
public:
	void meetVisitor(const Professor &) const;
};

//** Body of the meetVisitor method of the Rector
// The input parameter is a reference to Professor (Base) class
void Rector::meetVisitor(const Professor& visitor) const
{
	visitor.print();		// polymorphism
}

// A main progra to test the meetVisitor
int main()
{
	Rector itu_rector;
	Professor prof1("Professor 1", "Robotics");
	Dean dean1("Dean 1","Computer Networks","Faculty of Computer and Informatics Engineering");

	char c;					// To read from keyboard
	do {
		cout << "Professor or Dean (p / d / else: exit)"; std::cin >> c;
		if (c == 'p') itu_rector.meetVisitor(prof1);
		if (c == 'd') itu_rector.meetVisitor(dean1); 
	}while(c == 'p'|| c == 'd');
	return 0;
}