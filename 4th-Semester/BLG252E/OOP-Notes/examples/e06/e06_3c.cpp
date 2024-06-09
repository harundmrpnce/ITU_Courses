// e06_3c.cpp
// whole-part objects , orders of constructors and destructors

#include <iostream>
using std::cout;
using std::endl;

// The Part class has a default constructor and a destructor
class Part{
 public:
	 Part(){ cout << "Default Constructor of the Part" << endl;}
	 ~Part(){ cout << "Destructor of the Part" << endl;}
private:
};

// The Whole class. Contains two objects of the class Part as members 
// The Whole class has a default constructor and a destructor
class Whole {
public:
	Whole() { cout << "Default Constructor of the Whole" << endl; }
	~Whole() { cout << "Destructor of the Whole" << endl; }
private:
	Part m_part1, m_part2;				// Two member objects
};

// ----- Main Function -----
int main()
{
	Whole objectWhole;
	return 0;
}