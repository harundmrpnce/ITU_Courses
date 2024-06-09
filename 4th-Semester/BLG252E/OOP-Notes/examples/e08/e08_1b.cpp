// e08_1b.cpp
// Polymorphism
// Calling a virtual function pointed by a poniter 

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
	void meetVisitor(const Professor *) const;
};

//** Body of the meetVisitor method of the Rector
// The input parameter is a pointer to Professor (Base) class
void Rector::meetVisitor(const Professor* visitor) const
{
	visitor->print();		// Polymorphism
}

// A main progra to test the meetVisitor
int main()
{
	Rector itu_rector;
	Professor prof1("Professor 1", "Robotics");
	Dean dean1("Dean 1","Computer Networks","Faculty of Computer and Informatics Engineering");

	Professor *ptr;			// A pointer to Base type
	char c;					// To read from keyboard
	do {
		cout << "Professor or Dean (p / d / else: Dean and exit)"; std::cin >> c;
		if (c == 'p') ptr = &prof1;
		     else     ptr = &dean1; 
		itu_rector.meetVisitor(ptr);		// which print
	}while(c == 'p'|| c == 'd');
	return 0;
}