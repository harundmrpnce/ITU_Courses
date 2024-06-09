/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<27.10.2023>*/

#include <iostream>
#include <fstream>
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

// Function to count the number of lines in a file
int findSize(const string csvFile) {
    ifstream file(csvFile);

    if (!file.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
        return 0;
    }

    string line;
    int i = 0;
    while (getline(file, line)) {
        i++;
    } 
    file.close();
    return i-1; // Subtract 1 to exclude the header line
}

// Function to read data from a CSV file and store it in an array of Employee objects
void readFile(const string csvFile, Employee* emps) {
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
        emps[id-1].setID(id);
        emps[id-1].setSalary(salary);
        emps[id-1].setDepartment(department);
    } 
    file.close();
}

// Function to add a new Employee to the array
void addEmployee(Employee* &emps, int salary, int department, int &size, int &maxID) {
    // Create a new array with one more element
    Employee *newEmps = new Employee[size + 1];

    // Copy existing Employee objects to the new array
    for (int i = 0; i < size; i++) {
        newEmps[i] = emps[i];
    }

    // Release memory occupied by the old array
    delete[] emps;

    // Update the array pointer to the new array
    emps = newEmps;

    emps[size].setID(++maxID);
    emps[size].setSalary(salary);
    emps[size].setDepartment(department);
    size++;
}

// Function to update an existing Employee's information
void updateEmployee(Employee* &emps, int id, int salary, int department, int &size) {
    bool isValid = false;
    
    // Find the Employee with the specified ID
    for (int i = 0; i < size; i++) {
        if (emps[i].getID() == id) {
            isValid = true;
            emps[i].setSalary(salary);
            emps[i].setDepartment(department);
        }
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
}

// Function to delete an Employee from the array
void deleteEmployee(Employee* &emps, int id, int &size) {

    // Check if the array of Employees is empty
    if (size == 0) {
        cout << "ERROR: There is no Employee\n";
        return;
    }

    bool isValid = false;

    // Find the Employee with the specified ID
    for (int i = 0; i < size; i++) {
        if (emps[i].getID() == id) {
        isValid = true;
        break;
        }
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to delete\n";
        return;
    }

    // Create a new array with one less element
    Employee *newEmps = new Employee[size-1];
    int j = 0;

    // Copy Employee objects except the one to be deleted to the new array
    for (int i = 0; i < size; i++) {
        if (emps[i].getID() != id) {
            newEmps[j] = emps[i];
            j++;
        }
    }

    // Release memory occupied by the old array
    delete[] emps;

    // Update the array pointer to the new array
    emps = newEmps;
    size--;

}

// Function to perform operations based on a text file
void operation(const string txtFile, Employee* &emps, int &size, int &maxID) {
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
            deleteEmployee(emps, id, size);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } else if (operation == "ADD") {
            clock_t start = clock();
            file >> salary >> comma >> department;
            addEmployee(emps, salary, department, size, maxID);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } else if (operation == "UPDATE") {
            clock_t start = clock();
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(emps, id, salary, department, size);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    } 
    file.close();
}

// Function to write the data of Employees to a CSV file
void writeFile(Employee* emps, int &size) {
    ofstream file("array_solution.csv");
    file << "Employee_ID;Salary;Department\n";
    for (int i = 0; i < size; i++) {
        file << emps[i].getID() << ';' << emps[i].getSalary() << ';' << emps[i].getDepartment() << "\n";
    } 
    file.close();
}

int main(int argc, char **argv) {
    int maxID = findSize(argv[1]);
    int size = findSize(argv[1]);
    
    Employee *employees = new Employee[size];
    
    readFile(argv[1], employees);
    operation(argv[2], employees, size, maxID);
    writeFile(employees, size);

    delete[] employees;

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}