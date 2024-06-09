/*
@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<31.12.2023>
*/

#include <iostream>
#include <fstream>
#include <random>
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

class QuadruplySkipList_Node {
private:
    Employee* data;
    QuadruplySkipList_Node* next;
    QuadruplySkipList_Node* prev;
    QuadruplySkipList_Node* below;
    QuadruplySkipList_Node* above;


public:
    QuadruplySkipList_Node(Employee* data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
        this->below = nullptr;
        this->above = nullptr;
    }

    Employee* getData() {
        return this->data;
    }

    QuadruplySkipList_Node* getNext() {
        return this->next;
    }

    QuadruplySkipList_Node* getPrev() {
        return this->prev;
    }

    QuadruplySkipList_Node* getBelow() {
        return this->below;
    }

    QuadruplySkipList_Node* getAbove() {
        return this->above;
    }

    void setData(Employee* data) {
        this->data = data;
    }

    void setNext(QuadruplySkipList_Node* next) {
        this->next = next;
    }

    void setPrev(QuadruplySkipList_Node* prev) {
        this->prev = prev;
    }

    void setBelow(QuadruplySkipList_Node* below) {
        this->below = below;
    }

    void setAbove(QuadruplySkipList_Node* above) {
        this->above = above;
    }
};

class QuadruplySkipList {
private:
    QuadruplySkipList_Node* head;
    int height;

    QuadruplySkipList_Node* buildNode(Employee* data, bool isHead = false) { // create a new node corresponding to flip coin
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, 1);
        
        int coin = distribution(gen);
        int currentHeight = 1;
        QuadruplySkipList_Node* root = new QuadruplySkipList_Node(data);
        QuadruplySkipList_Node* temp = root;
        while (currentHeight < height && (isHead || coin == 1)) {
            QuadruplySkipList_Node* newNode = new QuadruplySkipList_Node(data);
            temp->setAbove(newNode);
            newNode->setBelow(temp);
            temp = newNode;
            coin = distribution(gen);
            currentHeight++;
        }
        return temp;
    }

public:
    QuadruplySkipList(int height) {
        this->height = height;
        this->head = buildNode(new Employee(-1, 0, 0), true);
    }

    ~QuadruplySkipList() {
        QuadruplySkipList_Node* current = head;
        QuadruplySkipList_Node* belowTemp = current;
        while (belowTemp) {
            belowTemp = current->getBelow();  // hold the below node
            while (current) {
                QuadruplySkipList_Node* temp = current; // hold the current node
                current = current->getNext();
                if (!temp->getBelow())
                    delete temp->getData(); // delete the employee object
                delete temp; // delete the current node
            }
            current = belowTemp; // go to the below node
        }
    }

    Employee* search(int search_id) {
        QuadruplySkipList_Node* current = head;
        while (current) {
            if (current->getData()->getID() == search_id)
                return current->getData();
            else if (current->getNext() == nullptr || current->getNext()->getData()->getID() > search_id) {
                current = current->getBelow();
            } else {
                current = current->getNext();
            }
        }
        return nullptr;
    }

    void insert(Employee* data) {
        QuadruplySkipList_Node* current = head;

        while (true) {
            while (current->getNext() && current->getNext()->getData()->getID() < data->getID())
                current = current->getNext();
            if (current->getBelow())
                current = current->getBelow();
            else
                break;
        }
        // the belowest prev node found

        QuadruplySkipList_Node* aboveestAdded = buildNode(data);
        QuadruplySkipList_Node* root = aboveestAdded;
        while (root->getBelow()) {
            root = root->getBelow();
        }
        // hold the belowest added node

        while (root) {
            if (current->getNext()) {
                root->setNext(current->getNext());
                root->setPrev(current);
                current->getNext()->setPrev(root);
                current->setNext(root);
            } else {
                current->setNext(root);
                root->setPrev(current);
            }
            if (root->getAbove()) { 
                root = root->getAbove(); 
                while (!current->getAbove()) {
                    current = current->getPrev();
                }
                current = current->getAbove();  // find the new position for the added node
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
        
        QuadruplySkipList_Node* current = head;
        QuadruplySkipList_Node* deletedNode;
        while (true) {
            while (current->getNext() && current->getNext()->getData()->getID() < remove_id)
                current = current->getNext();
            if (current->getNext() && current->getNext()->getData()->getID() == remove_id) {
                deletedNode = current->getNext();
                break;
            }
            if (current->getBelow())
                current = current->getBelow();
        }   

        while (deletedNode) {
            QuadruplySkipList_Node* temp = deletedNode;
            current->setNext(deletedNode->getNext());
            if (deletedNode->getNext()) {
                deletedNode->getNext()->setPrev(current);
            }
            deletedNode = deletedNode->getBelow();
            if (deletedNode) {
                current = deletedNode->getPrev();
            }
            if (!temp->getBelow())
                delete temp->getData();
            delete temp;
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
        QuadruplySkipList_Node* current = head;
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

void fillSkipList(const string fileName, QuadruplySkipList* skipList, int &maxID) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error opening file" << fileName << endl;
        return;
    }

    string line;
    int id, salary, department;
    char comma;

    getline(inputFile, line); 

    while(inputFile >> id >> comma >> salary >> comma >> department) {
        Employee* employee = new Employee(id, salary, department);
        skipList->insert(employee);
        if (id > maxID)
            maxID = id;
    }
    inputFile.close();
}

void operation(const string fileName, QuadruplySkipList* skipList, int &maxID) {
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
            clock_t start = clock();
            skipList->remove(id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } 
        else if (operation == "ADD") {
            operationFile >> salary >> comma >> department;
            clock_t start = clock();
            Employee* added = new Employee(++maxID, salary, department);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } 
        else if (operation == "UPDATE") {
            operationFile >> id >> comma >> salary >> comma >> department;
            clock_t start = clock();
            skipList->update(id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    } 
    operationFile.close();
}

int main(int argc, char* argv[]) {
    QuadruplySkipList* skipList = new QuadruplySkipList(10);
    int maxID = 0;
    fillSkipList(argv[1], skipList, maxID);
    operation(argv[2], skipList, maxID);

    ofstream outputFile("quadruply_output.csv");
    skipList->dumpToFile(outputFile);
    outputFile.close();

    delete skipList;

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}