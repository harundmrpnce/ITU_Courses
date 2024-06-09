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

// Function to find the maximum Employee ID from a CSV file
int findMaxID(const string csvFile) {
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

    return i - 1; // Subtract 1 to exclude the header line
}

// Function to copy content from one file to another
void copyFile(const string exName, const string newName) {
    ifstream exFile(exName);
    ofstream newFile(newName);

    string line;
    while(getline(exFile, line)) {
        newFile << line << '\n';
    }

    exFile.close();
    newFile.close();
}

// Function to delete an Employee from a CSV file
void deleteEmployee(const string csvFile, int idToDelete) {
    ifstream csv(csvFile);
    if (!csv.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
    }

    ofstream copyCsv("copy.csv");

    // Read and write the header line to the copy file
    string line;
    getline(csv, line);
    copyCsv << line << '\n';

    int id, salary, department;
    char comma;

    int i = 0;
    bool isValid = false;

    while (csv >> id >> comma >> salary >> comma >> department) {
        i++;
        if (idToDelete == id) {
            isValid = true;
            continue; // Skip writing the Employee to the copy file
        }
        // Write the Employee to the copy file (excluding the one to delete)
        copyCsv << id << ';' << salary << ';' << department << '\n';
    }

    // Handle potential error cases
    if (i == 0) {
        cout << "ERROR: There is no Employee\n";
    } else if (!isValid) {
        cout << "ERROR: An invalid ID to delete\n";
    }

    // Close the copy file and copy its content back to the original CSV file
    copyCsv.close();
    copyFile("copy.csv", csvFile);
}

// Function to add an Employee to a CSV file
void addEmployee(const string csvFile, int newSalary, int newDepartment, int &maxID) {
    // Open the copy file in append mode
    ofstream copyCsv("copy.csv", ios::app);

    // Increment the maximum Employee ID and append the new Employee to the copy file
    copyCsv << ++maxID << ';' << newSalary << ';' << newDepartment << '\n';

    // Close the copy file and copy its content back to the original CSV file
    copyCsv.close();
    copyFile("copy.csv", csvFile);
}

// Function to update an Employee's information in a CSV file
void updateEmployee(const string csvFile, int idToUpdate, int newSalary, int newDepartment) {

    ifstream csv(csvFile);
    if (!csv.is_open()) {
        cout << "The file cannot be found: " << csvFile << "\n";
    }

    ofstream copyCsv("copy.csv");

    // Read and write the header line to the copy file
    string line;
    getline(csv, line);
    copyCsv << line << '\n';

    int id, salary, department;
    char comma;
    bool isValid = false;

    while (csv >> id >> comma >> salary >> comma >> department) {
        if (id == idToUpdate) {
            // Write the updated Employee information to the copy file
            copyCsv << idToUpdate << ';' << newSalary << ';' << newDepartment << '\n'; 
            isValid = true;
        } else {
            // Write the existing Employee information to the copy file
            copyCsv << id << ';' << salary << ';' << department << '\n'; 
        }
    }

    // If no matching ID is found, display an error message
    if (!isValid) {
        cout << "ERROR: An invalid ID to update\n";
    }

    // Close the copy file and copy its content back to the original CSV file
    copyCsv.close();
    copyFile("copy.csv", csvFile);
}

// Function to perform operations based on a text file
void operation(const string csvFile, const string txtFile, int &maxID) {
    ifstream txt(txtFile);
    if (!txt.is_open()) {
        cout << "The file cannot be found: " << txtFile << "\n";
        return;
    }

    string operation;
    char comma;
    int id, salary, department;

    while (getline(txt, operation, ';')) {
        // Remove carriage return and newline characters if present
        if (!operation.empty() && operation.front() == '\r') {
            operation.erase(0, 2);
        } else if (!operation.empty() && operation.front() == '\n') {
            operation.erase(0, 1);
        }

        if (operation == "ADD") {
            clock_t start = clock();
            txt >> salary >> comma >> department;
            addEmployee(csvFile, salary, department, maxID);
            clock_t end = clock();
            addTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            addOperation++;
        } else  if (operation == "DELETE") {
            clock_t start = clock();
            txt >> id;
            deleteEmployee(csvFile, id);
            clock_t end = clock();
            deleteTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            deleteOperation++;
        } else if (operation == "UPDATE") {
            clock_t start = clock();
            txt >> id >> comma >> salary >> comma >> department;
            updateEmployee(csvFile, id, salary, department);
            clock_t end = clock();
            updateTime += (double)(end - start) * 1000 / CLOCKS_PER_SEC;
            updateOperation++;
        }
    }
}

int main(int argc, char *argv[]) {

    copyFile(argv[1], "copy.csv");
    int maxID = findMaxID(argv[1]);
    operation(argv[1], argv[2], maxID);
    remove("copy.csv");

    cout << "ADD: " << addTime / addOperation << "\n";
    cout << "DELETE: " << deleteTime / deleteOperation << "\n";
    cout << "UPDATE: " << updateTime / updateOperation << "\n";

    return 0;
}