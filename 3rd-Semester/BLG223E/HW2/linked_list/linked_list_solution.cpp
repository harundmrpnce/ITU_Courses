/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<10.11.2023>*/

#include <iostream>
#include <fstream>
#include <time.h>

double updateTime = 0;
double deleteTime = 0;
double addTime = 0;

int addOperation = 0;
int updateOperation = 0;
int deleteOperation = 0;

using namespace std;

class Employee {
    private:
        int id;
        int salary;
        int department;
        Employee *next;

    public:
        Employee() {
            id = 0;
            salary = 0;
            department = 0;
            next = nullptr;
        }

        void setNext(Employee *next) {
            this->next = next;
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

        Employee *getNext() {
            return this->next;
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

// Function to read data from a CSV file and store it in an linked list of Employee objects
void readFile(const string csvFile, Employee* &head, Employee* &tail) {
    ifstream file(csvFile);

    if (!file.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
        return;
    }
    string line;
    int id, salary, department;
    char comma;
    getline(file, line); // Read and discard the header line

    Employee *itr = head;

    while ((file >> id >> comma >> salary >> comma >> department)) {
        itr->setID(id);
        itr->setSalary(salary);
        itr->setDepartment(department);
        tail = itr;
        itr->setNext(new Employee());
        itr = itr->getNext();
    }

    if (head->getID() == 0) {
        head = nullptr;
        tail = nullptr;
    } else {
        tail->setNext(nullptr);
    }

    file.close();
}

// Function to add a new Employee to the array
void addEmployee(Employee* &head, Employee* &tail, int salary, int department, int &maxID) {
    Employee *newEmployee = new Employee();
    newEmployee->setID(++maxID);
    newEmployee->setSalary(salary);
    newEmployee->setDepartment(department);

    if (head == nullptr) {
        head = newEmployee;
        tail = head;
    } else {
        tail->setNext(newEmployee);
        tail = tail->getNext();
    }
}

// Function to update an existing Employee's information
void updateEmployee(Employee* head, int id, int salary, int department) {
    bool isValid = false;

    Employee *itr = head;

    // Find the Employee with the specified ID
    while (itr != nullptr) {
        if (itr->getID() == id) {
            isValid = true;
            itr->setSalary(salary);
            itr->setDepartment(department);
        }
        if (itr->getNext() == nullptr) break;
        itr = itr->getNext();
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
}

// Function to delete an Employee from the linked list
void deleteEmployee(Employee* &head, Employee* &tail, int id) {
    // check if the linked list is empty
    if (head == nullptr) {
        cout << "ERROR: There is no Employee\n";
        return;
    }

    bool isValid = false;

    Employee *itr = head;
    Employee *prev = itr;
    
    // delete specified id with check the index (deleting head, tail or between)
    while (itr != nullptr) {
        if (itr->getID() == id) {
            isValid = true;
            if (itr == head) {
                if (itr->getNext() == nullptr) {    
                    delete itr;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    head = itr->getNext();
                    itr->setNext(nullptr);
                    delete itr;
                }
            } else if (itr == tail) {
                tail = prev;
                tail->setNext(nullptr);
                delete itr;
            } else {
                prev->setNext(itr->getNext());
                itr->setNext(nullptr);
                delete itr;
            }
            break;
        }
        
        // update the prev and itr pointer
        if (itr->getNext() != nullptr) {
            prev = itr;
            itr = itr->getNext();
        } else break;
    }

    // check if the specified id deleted or not.
    if (!isValid) {
        cout << "ERROR: An invalid ID to delete\n";
    }
}

// Function to perform operations based on a text file
void operation(const string txtFile, Employee* &head, Employee* &tail, int &maxID) {
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
            deleteEmployee(head, tail, id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } else if (operation == "ADD") {
            clock_t start = clock();
            file >> salary >> comma >> department;
            addEmployee(head, tail, salary, department, maxID);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } else if (operation == "UPDATE") {
            clock_t start = clock();
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(head, id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    } 
    file.close();
}

// Function to write the data of Employees to a CSV file
void writeFile(Employee* &head) {
    ofstream file("1000k.csv");
    file << "Employee_ID;Salary;Department\n";

    Employee *itr = head;

    while (itr != nullptr) {
        file << itr->getID() << ';' << itr->getSalary() << ';' << itr->getDepartment() << "\n";
        itr = itr->getNext();
    }
    file.close();
}

int main(int argc, char **argv) {
    int maxID;
    
    Employee *employee_head = new Employee();
    Employee *employee_tail = employee_head;

    readFile(argv[1], employee_head, employee_tail);

    // find max id
    if (employee_head == nullptr) {
        maxID = 0;
    } else {
        maxID = employee_tail->getID();
    }

    operation(argv[2], employee_head, employee_tail, maxID);
    writeFile(employee_head);

    // free the memory
    Employee *itr = employee_head;
    while (itr != nullptr) {
        employee_head = itr->getNext();
        itr->setNext(nullptr);
        delete itr;
        itr = employee_head;
    }

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}
