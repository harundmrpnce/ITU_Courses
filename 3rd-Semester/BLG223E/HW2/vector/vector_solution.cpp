/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<9.11.2023>*/

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h> 

using namespace std;

double updateTime = 0;
double deleteTime = 0;
double addTime = 0;

int addOperation = 0;
int updateOperation = 0;
int deleteOperation = 0;

class Employee {
    private:
        int id;
        int salary;
        int department;

    public:
        Employee() {
            id = 0;
            salary = 0;
            department = 0;
        }

        void setID(int id) {
            this->id = id;
        }

        void setSalary(int salary) {
            this->salary = salary;
        }

        void setDepartment(int department) {
            this->department = department;
        }

        int getID() {
            return this->id;
        }

        int getSalary() {
            return this->salary;
        }

        int getDepartment() {
            return this->department;
        }
};

// Function to read data from a CSV file and store it in an array of Employee objects
void readFile(const string csvFile, vector<Employee> &emps) {
    ifstream file(csvFile);

    if (!file.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
        return;
    }
    string line;
    int id, salary, department;
    char comma;
    getline(file, line); // Read and discard the header line
    while ((file >> id >> comma >> salary >> comma >> department)) {
        Employee emp;
        emp.setID(id);
        emp.setSalary(salary);
        emp.setDepartment(department);
        emps.push_back(emp);
    } 
    file.close();
}

// Function to add a new Employee to the array
void addEmployee(vector<Employee> &emps, int salary, int department, int &maxID) {
    Employee emp;
    emp.setID(++maxID);
    emp.setSalary(salary);
    emp.setDepartment(department);
    emps.push_back(emp);
}

// Function to update an existing Employee's information
void updateEmployee(vector<Employee> &emps, int id, int salary, int department) {
    bool isValid = false;
    
    // Find the Employee with the specified ID, then update it
    for (Employee& emp : emps) {
        if (emp.getID() == id) {
            isValid = true;
            emp.setSalary(salary);
            emp.setDepartment(department);
            break;
        }
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
}

// Function to delete an Employee from the array
void deleteEmployee(vector<Employee> &emps, int id) {
    // Check if the array of Employees is empty
    if (emps.empty()) {
        cout << "ERROR: There is no Employee\n";
        return;
    }

    bool isValid = false;

    // Find the Employee with the specified ID then delete it
    for (auto it = emps.begin(); it != emps.end(); it++) {
        if (it->getID() == id) {
            isValid = true;
            emps.erase(it);
            break;
        }
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to delete\n";
        return;
    }
}

// Function to perform operations based on a text file
void operation(const string txtFile, vector<Employee> &emps, int &maxID) {
    ifstream file(txtFile);
    if (!file.is_open()) {
        cout << "The file cannot be found: " << txtFile << "\n";
        return;
    }
    string operation;
    char comma;
    int id, salary, department;

    while (getline(file, operation, ';')) {
        // Remove carriage return and newline characters if present
        if (!operation.empty() && operation.front() == '\r') {
            operation.erase(0, 2);
        } else if (!operation.empty() && operation.front() == '\n') {
            operation.erase(0, 1);
        }
        if (operation == "DELETE") {
            clock_t start = clock();
            file >> id;
            deleteEmployee(emps, id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } else if (operation == "ADD") {
            clock_t start = clock();
            file >> salary >> comma >> department;
            addEmployee(emps, salary, department, maxID);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } else if (operation == "UPDATE") {
            clock_t start = clock();
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(emps, id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    } 
    file.close();
}

// Function to write the data of Employees to a CSV file
void writeFile(vector<Employee> &emps) {
    ofstream file("vector_solution.csv");
    file << "Employee_ID;Salary;Department\n";
    for (Employee &emp: emps) {
        file << emp.getID() << ';' << emp.getSalary() << ';' << emp.getDepartment() << "\n";
    } 
    file.close();
}

int main(int argc, char **argv) {
    
    vector<Employee> employees;
    
    readFile(argv[1], employees);

    // Find the maximum id of the array
    int maxID = employees.empty() ? 0 : employees.back().getID();
    
    operation(argv[2], employees, maxID);
    writeFile(employees);

    employees.clear();

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}
