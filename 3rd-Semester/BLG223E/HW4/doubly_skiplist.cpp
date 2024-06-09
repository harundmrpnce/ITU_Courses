/*
@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<31.12.2023>
*/

#include <iostream>
#include <fstream>
#include <random>
// #include <time.h>  // update: 0.005ms, add: 0.03ms, delete: 0.008ms height: 5

using namespace std;

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

    int getID() {
        return id;
    }

    int getSalary() {
        return salary;
    }

    int getDepartment() {
        return department;
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
};

class DoublySkipList_Node {
private:
    Employee* data;
    DoublySkipList_Node* next;
    DoublySkipList_Node* below;

public:
    DoublySkipList_Node(Employee* data) {
        this->data = data;
        this->next = nullptr;
        this->below = nullptr;
    }

    Employee* getData() {
        return this->data;
    }

    DoublySkipList_Node* getNext() {
        return this->next;
    }

    DoublySkipList_Node* getBelow() {
        return this->below;
    }

    void setData(Employee* data) {
        this->data = data;
    }

    void setNext(DoublySkipList_Node* next) {
        this->next = next;
    }

    void setBelow(DoublySkipList_Node* below) {
        this->below = below;
    }
};

class DoublySkipList {
private:
    DoublySkipList_Node* head;
    int height;

    DoublySkipList_Node* buildNode(Employee* data, bool isHead, int &nodeHeight) { // create a new node corresponding to flip coin
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, 1);
        nodeHeight = 1;
        int coin = distribution(gen);
        DoublySkipList_Node* root = new DoublySkipList_Node(data);
        DoublySkipList_Node* temp = root;
        while (nodeHeight < height && (isHead || coin == 1)) {
            DoublySkipList_Node* newNode = new DoublySkipList_Node(data);
            temp->setBelow(newNode);
            temp = newNode;
            coin = distribution(gen);
            nodeHeight++;
        }
        return root;
    }

public:
    DoublySkipList(int height) {
        this->height = height;
        this->head = buildNode(new Employee(-1, 0, 0), true, height);
    }

    ~DoublySkipList() {
        DoublySkipList_Node* current = head;
        DoublySkipList_Node* belowTemp = current;
        while (belowTemp) {
            belowTemp = current->getBelow(); // hold the below node
            while (current) {
                DoublySkipList_Node* temp = current; // hold the current node
                current = current->getNext();
                if (!temp->getBelow()) 
                    delete temp->getData(); // delete the employee object
                delete temp; // delete the current node
            }
            current = belowTemp; // go to the below node
        }
    }

    Employee* search(int search_id) {
        DoublySkipList_Node* current = head;
        while (current) {
            if (current->getData()->getID() == search_id) {
                return current->getData();
            } else if (current->getNext() == nullptr || current->getNext()->getData()->getID() > search_id) {
                current = current->getBelow();
            } else {
                current = current->getNext();
            }
        }
        return nullptr;
    }

    void insert(Employee* data) {
        int nodeHeight = 0;
        DoublySkipList_Node* newNode = buildNode(data, false, nodeHeight);

        int skipListHeight = height;

        DoublySkipList_Node* current = head;
        for (int i = 0; i < skipListHeight - nodeHeight; i++) {
            while (current->getNext() && current->getNext()->getData()->getID() < data->getID())
                current = current->getNext();
            current = current->getBelow();
        }
        // current is now at the level where we want to insert the new node
        
        while (true) {
            while (current->getNext() && current->getNext()->getData()->getID() < data->getID())
                current = current->getNext();
            newNode->setNext(current->getNext());
            current->setNext(newNode);
            
            if (current->getBelow()) {
                current = current->getBelow();
                newNode = newNode->getBelow();
            }
            else
                break;
        }   
    }

    void remove(int remove_id) {
        if (!search(remove_id)) {
            cout << "ERROR: An invalid ID to delete\n";
            return;
        }

        DoublySkipList_Node* current = head;

        while (current) {
            while (current->getNext() && current->getNext()->getData()->getID() < remove_id)
                current = current->getNext();
            if (current->getNext() && current->getNext()->getData()->getID() == remove_id) {
                DoublySkipList_Node* deletedHead = current->getNext();
                DoublySkipList_Node* temp = deletedHead;
                while (true) {
                    while (current && current->getNext() && current->getNext()->getData()->getID() != remove_id)
                        current = current->getNext();
                    
                    current->setNext(temp->getNext());

                    if (current) {
                        DoublySkipList_Node *temp2 = temp;
                        current = current->getBelow();
                        temp = temp->getBelow();
                        if (temp2 && !temp2->getBelow()) {
                            delete temp2->getData();
                            delete temp2;
                            return;
                        }
                        delete temp2;
                    }
                }   
            }
            if (current->getBelow())
                current = current->getBelow();
            else
                break;
        }
    }

    void update(int id, int salary, int department) {
        Employee* employee = search(id);
        if (employee) {
            employee->setSalary(salary);
            employee->setDepartment(department);
        } else {
            cout << "ERROR: An invalid ID to update\n";
        }
    }

    void dumpToFile(ofstream& out_file) {
        DoublySkipList_Node* current = head;
        out_file << "Employee_ID;Salary;Department\n";
        while (current->getBelow()) {
            current = current->getBelow();
        }
        while (current) {
             if (current->getData()->getID() != -1) {
                out_file << current->getData()->getID() << ";" << current->getData()->getSalary() << ";" << current->getData()->getDepartment() << "\n";
            }
            current = current->getNext();
        }
    }
};

void fillSkipList(const string fileName, DoublySkipList* skipList, int &maxID) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error opening file" << fileName << endl;
        return;
    }

    string line;
    int id, salary, department;
    char comma;

    getline(inputFile, line);

    while (inputFile >> id >> comma >> salary >> comma >> department) {
        Employee* employee = new Employee(id, salary, department);
        skipList->insert(employee);
        if (id > maxID)
            maxID = id;
    }
    inputFile.close();
}

void operation(const string fileName, DoublySkipList* skipList, int &maxID) {
    ifstream operationFile(fileName);

    if (!operationFile.is_open()) {
        cout << "Error opening file" << fileName << endl;
        return;
    }

    string operation;
    int id, salary, department;
    char comma;

    while (getline(operationFile, operation, ';')) {
        // Remove carriage return and newline characters if present
        if (!operation.empty() && operation.front() == '\r') {
            operation.erase(0, 2);
        } else if (!operation.empty() && operation.front() == '\n') {
            operation.erase(0, 1);
        }
        if (operation == "DELETE") {
            operationFile >> id;
            // clock_t start = clock();
            skipList->remove(id);
            // clock_t end = clock();
            // cout << "The time of the delete employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
        } else if (operation == "ADD") {
            operationFile >> salary >> comma >> department;
            // clock_t start = clock();
            skipList->insert(new Employee(++maxID, salary, department));
            // clock_t end = clock();
            // cout << "The time of the add employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
        } else if (operation == "UPDATE") {
            operationFile >> id >> comma >> salary >> comma >> department;
            // clock_t start = clock();
            skipList->update(id, salary, department);
            // clock_t end = clock();
            // cout << "The time of the update employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
        }
    }

    operationFile.close();
}

int main(int argc, char* argv[]) {
    DoublySkipList* skipList = new DoublySkipList(10);
    int maxID = 0;
    fillSkipList(argv[1], skipList, maxID);
    operation(argv[2], skipList, maxID);

    ofstream outputFile("doubly_output.csv");
    skipList->dumpToFile(outputFile);
    outputFile.close();

    delete skipList;

    return 0;
}