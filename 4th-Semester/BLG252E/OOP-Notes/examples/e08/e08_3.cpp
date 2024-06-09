// e08_3.cpp
// Abstract class, pure virtual function

#include <iostream>
#include <string>
using std::cout;
using std::endl;

//*** Abstract base class: Employee
class Employee{      
public:
  Employee(const std::string&);						 // Constructor: name
  const std::string& getName() const { return m_name; } // A common method, not redefined
  virtual void print() const;						  // virtual function
  virtual double calculateSalary() const = 0;		  // pure virtual (abstract) function
private:
  std::string m_name;
};

//** Bodies of the methods of the Employee
// Constructor
Employee::Employee(const std::string& in_name) : m_name{ in_name }
{
	cout << "Constructor: Employee" << endl;
}

void Employee::print() const			// virtual function
{
	cout << "Name: "<< m_name << endl;
}

//*** Derived class: Worker
class Worker : public Employee{
public:
	Worker(const std::string&, unsigned int);    // Constructor: name, work hour
  void print() const override;                   // redefined(overriden)
  double calculateSalary() const override;		 //  concrete (implemented) virtual function
  void doWork() const;							 // A method specific to Worker
private:
	unsigned int m_workHour{};			  // work hours per month
};

//** Bodies of the methods of the Worker
// Constructor
Worker::Worker(const std::string& in_name, unsigned int in_workHour)
	                             : Employee{ in_name }, m_workHour{ in_workHour }
{
	cout << "Constructor: Worker" << endl;
}

void Worker::print() const     // redefined (overriden) virtual function
{
	Employee::print();
	cout << " I am a worker" << endl;
	cout << "My work Hours per month: " << m_workHour << endl;
}

// Concrete (implemented) virtual function
double Worker::calculateSalary() const 
{
	return 105* m_workHour;		// 105TL per hour
}

// A method specific to Worker
void Worker::doWork() const {
	cout << "I am working..." << endl;
}

//*** Derived class: Researcher
class Researcher : public Employee {
public:
	Researcher(const std::string&, unsigned int);    // Constructor: name, number of projects
	void print() const override;
	double calculateSalary() const override;		//  concrete (implemented) virtual function
	void doResearch() const;							 // A method specific to Researcher
private:
	unsigned int m_numofProjects{};			// the number of projects
};

//** Bodies of the methods of the Researcher
// Constructor
Researcher::Researcher(const std::string& in_name, unsigned int in_numofProjects)
	: Employee{ in_name }, m_numofProjects{ in_numofProjects }
{
	cout << "Constructor: Researcher" << endl;
}

void Researcher::print() const     // redefined (overriden) virtual function
{
	Employee::print();
	cout << " I am a researcher" << endl;
	cout << "Number of my projects: " << m_numofProjects << endl;
}

// Concrete (implemented) virtual function
double Researcher::calculateSalary() const     // virtual function
{
	switch (m_numofProjects) {
	  case 1: return 20000;
	  case 2: return 30000;
	  default: return 35000;
	}
}

// A method specific to Researcher
void Researcher::doResearch() const {
	cout << "I do research..." << endl;
}

// The main function for testing
int main()
{
	// Employee employee1{"Employee 1"};    // Error! Employee is an abstract class
	// Employee * employeePtr = new Employee {"Employee 1"};    // Error! Employee is an abstract class

	Employee* arrayOfEmployee[5]{};    // An array of pointers to Employe
	// Instead of an array std::vector or std::list can be used
	

	Worker worker1{ "Worker 1", 160 };		// Work hours per month = 160
	arrayOfEmployee[0] = &worker1;			// Address of the worker1 object to the array

	cout << "The name is " << arrayOfEmployee[0]->getName() << endl; // call the common function getName()
	//arrayOfEmployee[0]->doWork();			// Error! doWork() is not a base method. It is not at the interface

	Worker worker2{ "Worker 2", 150 };       // Work hours per month = 150
	arrayOfEmployee[1] = &worker2;

	Researcher researcher1{ "Researcher 1", 1 };        // The number of projects = 1
	arrayOfEmployee[2] = &researcher1;

	Worker worker3{ "Worker 3", 200 };      // Work hours per month = 200
	arrayOfEmployee[3] = &worker3;

	Researcher researcher2{ "Researcher 2", 3 };
	arrayOfEmployee[4] = &researcher2;

	for (unsigned int i = 0; i < 5; i++) {
		arrayOfEmployee[i]->print();
		cout << "Salary = " << arrayOfEmployee[i]->calculateSalary() << endl;
		cout << "--------------------" << endl;				// line break
	}
	return 0;
}