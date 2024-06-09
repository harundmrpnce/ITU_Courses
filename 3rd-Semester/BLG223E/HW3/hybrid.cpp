/*@Author
StudentName:<Harun Yahya Demirpençe>
StudentID:<150210022>
Date:<15.12.2023>*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <vector>
// #include <time.h>  // delete: 0.005ms ## add: 0.04ms ## update: 0.002ms shuffled ----- delete:0.03ms add:0.07ms update: 0.03ms ordered

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

        // breadth-first order traversal.
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

        // If the node to be deleted is the root
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
                this->root->setEmployee(min->getEmployee());  // Replace the root with the minimum node

                if (minParent->getLeft() == min) {
                    minParent->setLeft(min->getRight());
                } 
                else {
                    minParent->setRight(min->getRight());
                }
                min->setEmployee(deletedEmployee);  // Replace the minimum node with the root
                delete min;
            }
        } 
        // If the node to be deleted is not the root
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
                Employee *deletedEmployee = deletedNode->getEmployee();  // Replace the deleted node with the minimum node
                deletedNode->setEmployee(min->getEmployee());

                if (minParent->getLeft() == min) {
                    minParent->setLeft(min->getRight());
                } 
                else {
                    minParent->setRight(min->getRight());
                }
                min->setEmployee(deletedEmployee);  // Replace the minimum node with the deleted node
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

    // inorder traversal
    void printToFile(ofstream &outputFile) {
        stack<Node*> s;
        Node* current = this->root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->getLeft();
            }

            current = s.top();
            s.pop();
            outputFile << current->getEmployee()->getId() << ";"
                << current->getEmployee()->getSalary() << ";"
                << current->getEmployee()->getDepartment() << "\n";

            current = current->getRight();
        }
    }
};

// Return the number of nodes in the csv file
int nodeNum(const string csvFile) {
    ifstream file(csvFile);

    if (!file.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
        return 0;
    }

    string line;

    getline(file, line); // Skip the header line
    int nodeNum = 0;
    while (getline(file, line)) {
        nodeNum++;
    } 
    file.close();
    return nodeNum;
}

void fillTree(const string csvFile, vector<BinaryTree*>* &btVector, int &maxID) {
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
        btVector->at(id/5000)->insert(newEmployee); // Insert the employee to the corresponding tree
        if (id > maxID) maxID = id;  // Find the maximum ID
    } 
    file.close();
}

void deleteEmployee(vector<BinaryTree*>* &btVector, int id) {
    // clock_t start = clock();
    if (id >= 5000 * int(btVector->size())) { // If the ID is greater than the maximum ID
        cout << "ERROR: An invalid ID to delete\n";
        return;
    }
    btVector->at(id/5000)->remove(id);
    // clock_t end = clock();
    // cout << "The time of the delete employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
}

void addEmployee(vector<BinaryTree*>* &btVector, int salary, int department, int &maxID, int &nodeCount) {
    // clock_t start = clock();
    Employee* newEmployee = new Employee(++maxID, salary, department);
    nodeCount++;
    if (nodeCount % 5000 == 0) {
        btVector->push_back(new BinaryTree());  // Create a new tree for 5001st node
    }
    btVector->back()->insert(newEmployee);
    // clock_t end = clock();
    // cout << "The time of the add employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
}

void updateEmployee(vector<BinaryTree*>* &btVector, int id, int salary, int department) {
    // clock_t start = clock();
    if (id >= 5000 * int(btVector->size())) {  // If the ID is greater than the maximum ID
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
    btVector->at(id/5000)->update(id, salary, department);
    // clock_t end = clock();
    // cout << "The time of the update employee function(ms): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << '\n';
}

// Function to perform operations based on a text file
void operation(const string operationFile, vector<BinaryTree*>* &btVector, int &maxID, int &nodeCount) {
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
            file >> id;
            deleteEmployee(btVector, id);
        } 
        else if (operation == "ADD") {
            file >> salary >> comma >> department;
            addEmployee(btVector, salary, department, maxID, nodeCount);
        } 
        else if (operation == "UPDATE") {
            file >> id >> comma >> salary >> comma >> department;
            updateEmployee(btVector, id, salary, department);
        }
    } 
    file.close();
}

int main(int argc, char **argv) {
    vector<BinaryTree*>* btVector = new vector<BinaryTree*>();
    int maxID = 0;
    int nodeCount = nodeNum(argv[1]);  
    for (int i = 0; i < nodeCount / 5000 + 1; i++) {
        btVector->push_back(new BinaryTree()); // Create a new tree for every 5000 nodes
    }
    fillTree(argv[1], btVector, maxID);
    operation(argv[2], btVector, maxID, nodeCount);
    ofstream outputFile("output.csv");
    outputFile << "Employee_ID;Salary;Department\n";
    for (auto bt = btVector->begin(); bt != btVector->end(); bt++) {
        (*bt)->printToFile(outputFile);
        delete *bt;
    }
    delete btVector;
    outputFile.close();

    return 0;
}