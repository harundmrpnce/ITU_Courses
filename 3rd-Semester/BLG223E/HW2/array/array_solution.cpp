/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<7.11.2023>*/

#include <iostream>
#include <fstream>
// #include <time.h>  // delete: 0.5ms ## add: 0.4ms ## update: 0.1ms

using namespace std;

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
    // clock_t start = clock();

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

    // clock_t end = clock();
    // cout << "The time of the add employee function(ms): " << (double)(end - start) * 100 / CLOCKS_PER_SEC << '\n';
}

// Function to update an existing Employee's information
void updateEmployee(Employee* &emps, int id, int salary, int department, int &size) {
    // clock_t start = clock();

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

    // clock_t end = clock();
    // cout << "The time of the update employee function(ms): " << (double)(end - start) * 100 / CLOCKS_PER_SEC << '\n';
}

// Function to delete an Employee from the array
void deleteEmployee(Employee* &emps, int id, int &size) {
    // clock_t start = clock();

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

    // clock_t end = clock();
    // cout << "The time of the delete employee function(ms): " << (double)(end - start) * 100 / CLOCKS_PER_SEC << '\n';
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
            file >> id;
            deleteEmployee(emps, id, size);
        } else if (operation == "ADD") {
            file >> salary >> comma >> department;
            addEmployee(emps, salary, department, size, maxID);
        } else if (operation == "UPDATE") {
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(emps, id, salary, department, size);
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

    return 0;
}