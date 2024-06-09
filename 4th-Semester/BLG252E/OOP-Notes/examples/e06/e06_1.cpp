// e06_1.cpp
// Aggregation, has-a relationship
// An active course has a classroom

#include <iostream>
#include <string>
using std::cout;
using std::endl;

// *** The Class to represent classrooms
class ClassRoom {	           // Declaration/definition of the Classroom
public:
	ClassRoom(const std::string&, const std::string&, unsigned int);	  // Constructor to initialize building, id, and the capacity
	// Getters:
	const std::string& getBuilding() const { return m_building; }         // Accessor for the building
	const std::string& getId() const { return m_id; }					 // Accessor for the id
	unsigned int getCapacity() const { return m_capacity; }			     // Accessor for the capacity
	~ClassRoom();                                                        // Destructor, only to observe the lifecycle
private:
	std::string m_building;
	std::string m_id;
	unsigned int m_capacity{};	  // capacity initialized to zero
};

// ***** Bodies of Member Functions of the ClassRoom *****

// Constructor to initialize building, id, and the capacity
ClassRoom::ClassRoom(const std::string& in_building, const std::string& in_id, unsigned int in_capacity)
	: m_building{ in_building }, m_id{ in_id }, m_capacity{ in_capacity }
{
	cout << "Constructor of the ClassRoom is called..." << endl;
}
// Destructor
// Destructor is not necessary for this class
// We write it only to see when the life of the objects end
ClassRoom::~ClassRoom() {                                                       // Destructor, only to observe the lifecycle
	cout << "Destructor of the ClassRoom is called..." << endl;				// Only prints a message
}


// *** The Class to represent active courses
class Course {														// Declaration/definition of the Course
public:
	Course(const std::string&, unsigned int, const ClassRoom*);		// Constructor to initialize crn, number of students and the classroom of the course
	bool isAvailable() const;										// Returns true if there are available seats
	// Getters:
	const std::string& getCrn() const { return m_crn; }
	const ClassRoom* getClassRoom() const { return m_classRoom; }
	// Setter:
	void setClassRoom(const ClassRoom* newRoom) { m_classRoom = newRoom; }
	~Course();                                                        // Destructor, only to observe the lifecycle
private:
	std::string m_crn;
	unsigned int m_numOfStudents{};	    // number of students
	const ClassRoom* m_classRoom;		// The course has a classroom!! Has-a relationship
};

// ***** Bodies of Member Functions of the Course *****

// Constructor to initialize crn, number of students, and the classroom
Course::Course(const std::string& in_crn, unsigned int in_numOfStudents, const ClassRoom* in_classRoom )
	: m_crn{ in_crn }, m_numOfStudents{ in_numOfStudents }, m_classRoom{in_classRoom}
{
	cout << "Constructor of the Course is called..." << endl;
}
// Returns true if there are available seats in the assigned classroom
bool Course::isAvailable() const {
	return m_classRoom->getCapacity() > m_numOfStudents;
}
// Destructor
// Destructor is not necessary for this class
// We write it only to see when the life of the objects end
Course::~Course() {                                                       // Destructor, only to observe the lifecycle
	cout << "Destructor of the Course is called..." << endl;				// Only prints a message
}
// -------- Main Program -------------
int main()
{
	ClassRoom classRoom1{ "EEB", "D5102", 100 };			// Classrooms are created independently
	ClassRoom classRoom2{ "MED", "A102", 120 };

	cout << "----------------------" << endl; // Seperator
	{	// New scope only to monitor the lifetimes of the objects				
		Course BLG252E{ "23135", 110, &classRoom2 };
		Course YZV321{ "22338", 120, &classRoom2 };				// classRoom A102 belongs to two different courses
		if (BLG252E.isAvailable()) {
			cout << "There are available seats in the classroom of " << BLG252E.getCrn() << endl;
			cout << "The classroom " << BLG252E.getClassRoom()->getId() << " is in " << BLG252E.getClassRoom()->getBuilding() << endl;
		}
		else
			cout << "There are not available seats in the classroom of " << BLG252E.getCrn() << endl;

		if (YZV321.isAvailable()) {
			cout << "There are available seats in the classroom of " << YZV321.getCrn() << endl;
			cout << "The classroom " << YZV321.getClassRoom()->getId() << " is in " << YZV321.getClassRoom()->getBuilding() << endl;
		}
		else
			cout << "There are not available seats in the classroom of " << YZV321.getCrn() << endl;
		
		cout << "----------------------" << endl; // Seperator
		YZV321.setClassRoom(&classRoom1);     // Change the classroom of the course YZV321
		cout << "The new classroom " << YZV321.getClassRoom()->getId() << " is in " <<
			 YZV321.getClassRoom()->getBuilding() << endl;
		
		cout << "---- The scope of the course objects ends ----" << endl;
	}	// End of the scope of the course objects
	
		// Course objects do not exist, Classrooms still exist
	cout << "Classroom " << classRoom2.getId() << " is in the building " << classRoom2.getBuilding()
		<< " and has the capacity " << classRoom2.getCapacity() << endl;

	cout << "---- New courses are created ----" << endl;
	Course BLG468E{ "23158", 70, &classRoom2 };				// classRoom A102 asigned to a new course
	Course BLG454E{ "23160", 60, &classRoom1 };				// classRoom D5102 asigned to a course
	if (BLG468E.isAvailable()) cout << "There are available seats in the classroom" << endl;
	else cout << "The classroom is full" << endl;

	return 0;
}