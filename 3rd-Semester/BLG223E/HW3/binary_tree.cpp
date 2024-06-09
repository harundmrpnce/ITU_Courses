/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<15.12.2023>*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
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

class Node {
private:
    Employee* employee;
    Node* left;
    Node* right;

public:
    Node(Employee* employee) {
        this->employee = employee;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        if (this->employee != nullptr) delete this->employee;
    }

    void setEmployee(Employee* employee) {
        this->employee = employee;
    }

    void setLeft(Node* left) {
        this->left = left;
    }

    void setRight(Node* right) {
        this->right = right;
    }

    Employee* getEmployee() {
        return this->employee;
    }

    Node* getLeft() {
        return this->left;
    }

    Node* getRight() {
        return this->right;
    }

    int childNum() {
        if (this->left != nullptr && this->right != nullptr) {
            return 2;
        } 
        else if (this->left != nullptr || this->right != nullptr) {
            return 1;
        } 
        else {
            return 0;
        }
    }
};

class BinaryTree { 
private:
    Node* root;

public:
    BinaryTree() {
        this->root = nullptr;
    }

    ~BinaryTree() {
        queue<Node*> q;
        if (this->root != nullptr) q.push(this->root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->getLeft() != nullptr) {
                q.push(current->getLeft());
            }
            if (current->getRight() != nullptr) {
                q.push(current->getRight());
            }
            delete current;
        }
    }

    Node* findMin(Node* node) {
        while (node->getLeft() != nullptr) {
            node = node->getLeft();
        }
        return node;
    }

    Employee *search(int id) {
        Node* temp = this->root;
        while (temp != nullptr) {
            if (temp->getEmployee()->getId() > id) {
                temp = temp->getLeft();
            }
            else if (temp->getEmployee()->getId() < id) {
                temp = temp->getRight();
            }
            else {
                break;
            }
        }
        if (temp == nullptr) return nullptr;
        else return temp->getEmployee();
    }

    Node *findParent(int id) {
        Node* temp = this->root;
        Node* parent = nullptr;
        while (temp != nullptr) {
            if (temp->getEmployee()->getId() > id) {
                parent = temp;
                temp = temp->getLeft();
            }
            else if (temp->getEmployee()->getId() < id) {
                parent = temp;
                temp = temp->getRight();
            }
            else {
                break;
            }
        }
        return parent;
    }

    void insert(Employee *employee) {
        Node* newNode = new Node(employee);
        if (this->root == nullptr) {
            this->root = newNode;
        }
        else {
            Node* parent = findParent(employee->getId());
            if (employee->getId() > parent->getEmployee()->getId()) {
                parent->setRight(newNode);
            } 
            else if (employee->getId() < parent->getEmployee()->getId()) {
                parent->setLeft(newNode);
            }
            else {
                delete newNode;
                return;
            }
        } 
    }

    void remove(int id) {
        Employee* deleted = search(id);
        if (this->root == nullptr) {
            cout << "ERROR: There is no employee\n";
            return;
        } 
        else if (deleted == nullptr) {
            cout << "ERROR: An invalid ID to delete\n";
            return;
        }

        Node* parent = findParent(id);
        if (parent == nullptr) {
            if (this->root->childNum() == 0) {
                delete this->root;
                this->root = nullptr;
            } 
            else if (this->root->childNum() == 1) {
                Node* temp = this->root;
                if (this->root->getLeft() != nullptr) {
                    this->root = this->root->getLeft();
                } 
                else {
                    this->root = this->root->getRight();
                }
                delete temp;
            }
            else {
                Node* min = findMin(this->root->getRight());
                Node* minParent = findParent(min->getEmployee()->getId());
                Employee *deletedEmployee = this->root->getEmployee();
                this->root->setEmployee(min->getEmployee());

                if (minParent->getLeft() == min) {
                    minParent->setLeft(min->getRight());
                } 
                else {
                    minParent->setRight(min->getRight());
                }
                min->setEmployee(deletedEmployee);
                delete min;
            }
        } 
        else {
            Node* deletedNode = nullptr;
            if (parent->getLeft() != nullptr && parent->getLeft()->getEmployee()->getId() == id)
                deletedNode = parent->getLeft();
            else
                deletedNode = parent->getRight();
                
            if (deletedNode->childNum() == 0) {
                if (parent->getLeft() == deletedNode) {
                    parent->setLeft(nullptr);
                } 
                else {
                    parent->setRight(nullptr);
                }
                delete deletedNode;
            } 
            else if (deletedNode->childNum() == 1) {
                if (deletedNode->getLeft() != nullptr) {
                    if (parent->getLeft() == deletedNode) {
                        parent->setLeft(deletedNode->getLeft());
                    } 
                    else {
                        parent->setRight(deletedNode->getLeft());
                    }
                } 
                else {
                    if (parent->getLeft() == deletedNode) {
                        parent->setLeft(deletedNode->getRight());
                    } 
                    else {
                        parent->setRight(deletedNode->getRight());
                    }
                }
                delete deletedNode;
            } 
            else {
                Node* min = findMin(deletedNode->getRight());
                Node* minParent = findParent(min->getEmployee()->getId());
                Employee *deletedEmployee = deletedNode->getEmployee();
                deletedNode->setEmployee(min->getEmployee());

                if (minParent->getLeft() == min) {
                    minParent->setLeft(min->getRight());
                } 
                else {
                    minParent->setRight(min->getRight());
                }
                min->setEmployee(deletedEmployee);
                delete min;
            }  
        }
    }

    void update(int id, int salary, int department) {
        Employee* searched = search(id); 
        if (searched == nullptr) {
            cout << "ERROR: An invalid ID to update\n";
            return;
        }
        searched->setSalary(salary);
        searched->setDepartment(department);
    }

    int findHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = findHeight(node->getLeft());
        int rightHeight = findHeight(node->getRight());
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }

    int getHeight() {
        return findHeight(this->root);
    }

    void printToFile(ofstream &outputFile) {
        stack<Node*> s;
        Node* current = this->root;

        outputFile << "Employee_ID;Salary;Department\n";

        while (current != nullptr || !s.empty()) {
            // Reach the leftmost node of the current subtree
            while (current != nullptr) {
                s.push(current);
                current = current->getLeft();
            }

            // Pop the node from the stack and print its information
            current = s.top();
            s.pop();
            outputFile << current->getEmployee()->getId() << ";"
                << current->getEmployee()->getSalary() << ";"
                << current->getEmployee()->getDepartment() << "\n";

            // Move to the right subtree
            current = current->getRight();
        }
    }

    void printToConsole() {
        stack<Node*> s;

        if (this->root != nullptr) s.push(this->root);

        while (!s.empty()) {
            Node* current = s.top();
            cout << 
            current->getEmployee()->getId() << ";"<< 
            current->getEmployee()->getSalary() << ";" << 
            current->getEmployee()->getDepartment() << "\n";

            s.pop();

            if (current->getRight() != nullptr) {
                s.push(current->getRight());
            }
            if (current->getLeft() != nullptr) {
                s.push(current->getLeft());
            }
        }
    }
};

void fillTree(const string csvFile, BinaryTree* &bt, int &maxID) {
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
        bt->insert(newEmployee);
        if (id > maxID) maxID = id;
    } 
    file.close();
}

void deleteEmployee(BinaryTree* &bt, int id) {
    bt->remove(id);
}

void addEmployee(BinaryTree* &bt, int salary, int department, int &maxID) {
    Employee* newEmployee = new Employee(++maxID, salary, department);
    bt->insert(newEmployee);
}

void updateEmployee(BinaryTree* &bt, int id, int salary, int department) {
    bt->update(id, salary, department);
}

void operation(const string operationFile, BinaryTree* &bt, int &maxID) {
    ifstream file(operationFile);
    if (!file.is_open()) {
        cout << "The file cannot be found: " << operationFile << "\n";
        return;
    }

    string operation, sline;
    istringstream features;
    char comma;
    int id, salary, department;

    while (getline(file, sline)) {
        if (!sline.empty() && sline.back() == '\r') {
            sline.pop_back();
        } 
        features.clear();
        features.str(sline.substr(sline.find(';')+1, sline.length()));
        operation = sline.substr(0, sline.find(';'));   
        if (operation == "DELETE") {
            clock_t start = clock();
            features >> id;
            deleteEmployee(bt, id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } 
        else if (operation == "ADD") {
            clock_t start = clock();
            features >> salary >> comma >> department;
            addEmployee(bt, salary, department, maxID);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } 
        else if (operation == "UPDATE") {
            clock_t start = clock();
            features >> id >> comma >> salary >> comma >> department;
            updateEmployee(bt, id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        } 
        else if (operation == "HEIGHT") {
            cout << "H " << bt->getHeight() << "\n";
        } 
        else if (operation == "PRINT") {
            cout << "P\n";  
            bt->printToConsole();
        }
    } 
    file.close();
}

int main(int argc, char **argv) {
    BinaryTree *bt = new BinaryTree();
    int maxID = 0;
    fillTree(argv[1], bt, maxID);
    operation(argv[2], bt, maxID);
    ofstream outputFile("output.csv");
    bt->printToFile(outputFile);
    outputFile.close();

    delete bt;

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}