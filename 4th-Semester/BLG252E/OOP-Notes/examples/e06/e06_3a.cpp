// e06_3a.cpp
// default default constructors in whole-part relation

#include <iostream>
using std::cout;
using std::endl;

// The Part class 
// This author does not provide a constructor
class Part{
 public:
	 void print() const {
		 cout << "Data of the Part = " << m_data << endl;
	 }
private:
	int m_data{ 5 };		// Member of Part initialized to 5
};

// The Whole class. Contains two objects of the class Part as members 
// This author does not provide a constructor
class Whole{
 public:
	 void print() const {
		 cout << "Part1 of the Whole:"<< endl;
		 m_part1.print();
		 cout << "Part2 of the Whole:" << endl;
		 m_part2.print();
	 }
private:
	Part m_part1, m_part2;				// Two member objects
};

// ----- Main Function -----
int main()
{
	Whole objectWhole;
	objectWhole.print();
	return 0;
}