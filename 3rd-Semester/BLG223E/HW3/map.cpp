/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<15.12.2023>*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
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
    Employee(int id, int salary, int department) {
        this->id = id;
        this->salary = salary;
        this->department = department;
    }

    void setId(int id) {
        this->id = id;
    }
    
    void setSalary(int salary) {
        this->salary = salary;
    }

    void setDepartment(int department) {
        this->department = department;
    }

    int getId() {
        return this->id;
    }

    int getSalary() {
        return this->salary;
    }      

    int getDepartment() {
        return this->department;
    }
};

void printToFile(map<int, Employee*> &employeeMap, ofstream &outputFile) {
    outputFile << "Employee_ID;Salary;Department\n";
    for (const auto& entry : employeeMap) {
        outputFile 
        << entry.second->getId() << ";"
        << entry.second->getSalary() << ";"
        << entry.second->getDepartment() << "\n";
    }
}

void deleteEmployee(map<int, Employee*> &employeeMap, int id) {
    auto it = employeeMap.find(id);
    if (it != employeeMap.end()) {
        delete it->second; // delete the employee object
        employeeMap.erase(it);
    } else {
        cout << "ERROR: An invalid ID to delete\n";
    }
}

void addEmployee(map<int, Employee*> &employeeMap, int &maxID, int salary, int department) {
    Employee* newEmployee = new Employee(++maxID, salary, department);
    employeeMap[maxID] = newEmployee;
}

void updateEmployee(map<int, Employee*> &employeeMap, int id, int salary, int department) {
    auto it = employeeMap.find(id);
    if (it != employeeMap.end()) {
        it->second->setSalary(salary);
        it->second->setDepartment(department);
    } else {
        cout << "ERROR: An invalid ID to update\n";
    }
}

void fillMap(const string csvFile, map<int, Employee*> &employeeMap, int &maxID) {
    ifstream file(csvFile);

    if (!file.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
        return;
    }

    string line;
    int id, salary, department;
    char comma;

    getline(file, line); // Skip the header line

    while (file >> id >> comma >> salary >> comma >> department) {
        Employee* newEmployee = new Employee(id, salary, department);
        employeeMap[id] = newEmployee;
        if (id > maxID) maxID = id;
    } 

    file.close();
}

void operation(const string operationFile, map<int, Employee*> &employeeMap, int &maxID) {
    ifstream file(operationFile);
    if (!file.is_open()) {
        cout << "The file cannot be found: " << operationFile << "\n";
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
            deleteEmployee(employeeMap, id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } 
        else if (operation == "ADD") {
            clock_t start = clock();
            file >> salary >> comma >> department;
            addEmployee(employeeMap, maxID, salary, department);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } 
        else if (operation == "UPDATE") {
            clock_t start = clock();
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(employeeMap, id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    } 
    file.close();
}

int main(int argc, char **argv) {
    map<int, Employee*> employeeMap;
    int maxID = 0;

    fillMap(argv[1], employeeMap, maxID);
    operation(argv[2], employeeMap, maxID);

    ofstream outputFile("output.csv");
    printToFile(employeeMap, outputFile);
    outputFile.close();

    // Delete the employee objects
    for (const auto& entry : employeeMap) {
        delete entry.second; 
    }

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}