// e08_4a.cpp
// Design to interface
// The Accounting class is designed according to the base class Employee

#include <iostream>
#include <string>
#include <vector>	// smart array in the library
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
  void print() const override;                   // redefined(overridden)
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

void Worker::print() const     // redefined (overridden) virtual function
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


//*** Accounting class. Designed according to Employee
class Accounting {
public:
	Accounting() = default;						      // Default Constructor
	void addEmployee(const Employee*);                // Add an employee to the accounting system
	void printAll() const;					         // print all employees in the accounting system
	double collectSalaries() const;				     // calculate the sum of all salaries 
private:
	std::vector<const Employee*> m_employees;			// vector (array) of Employees
};

//** Bodies of the methods of the Accounting

// Add an employee to the accounting system
void Accounting::addEmployee(const Employee* in_employee)
{
	m_employees.push_back(in_employee);				// write the pointer to the vector
}

// print all employees in the accounting system
void Accounting::printAll() const			
{
	for (unsigned int i = 0; i < m_employees.size(); i++)
		m_employees[i]->print();						// print the ith employee
	cout << "---------------" << endl;					// line break
}

// calculate the sum of all salaries 
double Accounting::collectSalaries() const
{
	double sum{};
	for (unsigned int i = 0; i < m_employees.size(); i++)
		sum += m_employees[i]->calculateSalary();						// sum of salaries
	return sum;
}

// The main function for testing
int main()
{
	Accounting accountingSystem;				// An array of pointers to Employe
	
	Worker worker1{ "Worker 1", 160 };		// Work hours per month = 160
	accountingSystem.addEmployee(&worker1);			// Address of the worker1 object to the accounting system

	Worker worker2{ "Worker 2", 150 };       // Work hours per month = 150
	accountingSystem.addEmployee(&worker2);			// Address of the worker2 object to the accounting system

	Researcher researcher1{ "Researcher 1", 1 };        // The number of projects = 1
	accountingSystem.addEmployee(&researcher1);			// Address of the researcher1 object to the accounting system

	Worker worker3{ "Worker 3", 200 };      // Work hours per month = 200
	accountingSystem.addEmployee(&worker3);			// Address of the worker3 object to the accounting system

	Researcher researcher2{ "Researcher 2", 3 };
	accountingSystem.addEmployee(&researcher2);			// Address of the researcher2 object to the accounting system

	accountingSystem.printAll();			                       // Print all employees in the accounting system

	cout << "The total of the salaries = ";
	cout << accountingSystem.collectSalaries() << endl;			           // Print the sum of all salaries
	return 0;
}