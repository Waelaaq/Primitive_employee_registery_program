#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Employee {
    int id;
    string name;
    double salary;
    int yearsOfWork;
    int hoursWorked;
};

void saveEmployee(const Employee& emp) {
    ofstream outFile("EmployeesSaved.txt", ios::app);
    if (outFile.is_open()) {
        // Write employee details to file
        outFile << "ID: " << emp.id << endl;
        outFile << "Name: " << emp.name << endl;
        // Format salary to two decimal places
        outFile << "Salary: " << fixed << emp.salary << endl;
        outFile.unsetf(ios_base::floatfield); // Unset fixed formatting
        // Write other details
        outFile << "Years of Work: " << emp.yearsOfWork << endl;
        outFile << "Hours Worked: " << emp.hoursWorked << endl;
        outFile << "-----------------------" << endl;
        outFile.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

void hireEmployee(Employee employees[], int& numEmployees) {
    Employee newEmployee;
    cout << "---------------------------\n";
    cout << "Hire a new employee: " << endl;
    cout << "ID: ";
    cin >> newEmployee.id;
    cout << "Name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newEmployee.name); // Read the full name
    cout << "Salary: ";
    while (!(cin >> newEmployee.salary) || newEmployee.salary <= 0) { // Check if input for salary is valid
        cout << "Invalid input. Please enter a positive numeric value for salary: ";
        cin.clear(); // Clear error flags
        while (cin.get() != '\n'); // Discard invalid input
    }
    cout << "Number of years of work: ";
    cin >> newEmployee.yearsOfWork;
    cout << "Working hours this month: ";
    cin >> newEmployee.hoursWorked;

    saveEmployee(newEmployee); // Save employee to file
    employees[numEmployees] = newEmployee;
    numEmployees++;
}

int displayMenu(int choice) {
    cout << "---------------------------\n";
    cout << "1. Hire a new employee " << endl;
    cout << "2. Firing an employee " << endl;
    cout << "3. Ranked employee information " << endl;
    cout << "4. Find an employee " << endl;
    cout << "0. Exit " << endl;
    cout << "Choose action: ";

    return choice;
}

void fireEmployee(int employeeId) {
    ifstream inFile("EmployeesSaved.txt");
    ofstream tempFile("temp.txt");

    if (!inFile) {
        cout << "Unable to open file." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        if (line.find("ID: " + to_string(employeeId)) != string::npos) {
            found = true;
            cout << "The employee with ID " << employeeId << " was successfully fired." << endl;
            // Skip this record (employee to be fired)
            for (int i = 0; i < 4; ++i) {
                getline(inFile, line);
            }
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (!found) {
        cout << "The employee with ID " << employeeId << " was not found." << endl;
        remove("temp.txt");
    } else {
        remove("EmployeesSaved.txt");
        rename("temp.txt", "EmployeesSaved.txt");
    }
}

void sortEmployees(Employee employees[], int numEmployees, int sortBy) {
    switch (sortBy) {
        case 1: // by salary
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - 1 - i; j++) {
                    if (employees[j].salary > employees[j + 1].salary) {
                        Employee temp = employees[j];
                        employees[j] = employees[j + 1];
                        employees[j + 1] = temp;
                    }
                }
            }
            break;
        case 2: // by years of work
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - 1 - i; j++) {
                    if (employees[j].yearsOfWork > employees[j + 1].yearsOfWork) {
                        Employee temp = employees[j];
                        employees[j] = employees[j + 1];
                        employees[j + 1] = temp;
                    }
                }
            }
            break;
        case 3: // by hours Worked
            for (int i = 0; i < numEmployees - 1; i++) {
                for (int j = 0; j < numEmployees - 1 - i; j++) {
                    if (employees[j].hoursWorked > employees[j + 1].hoursWorked) {
                        Employee temp = employees[j];
                        employees[j] = employees[j + 1];
                        employees[j + 1] = temp;
                    }
                }
            }
    }
}

void displayEmployees(Employee employees[], int numEmployees) {
    cout << "---------------------------\n";
    cout << "Matt arranged staff: " << endl;
    cout << "--------------------------" << endl;
    for (int i = 0; i < numEmployees; i++) {
        cout << "ID: " << employees[i].id << endl;
        cout << "Name: " << employees[i].name << endl;
        cout << "Salary: " << employees[i].salary << endl;
        cout << "Number of years of work: " << employees[i].yearsOfWork << endl;
        cout << "Working hours this month: " << employees[i].hoursWorked << endl;
        cout << "--------------------------" << endl;
    }
}
void searchEmployeeSequential(Employee employees[], int numEmployees) {
    int searchId;
    cout << "---------------------------\n";
    cout << "Enter the employee ID you are looking for: ";
    cin >> searchId;

    bool found = false;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == searchId) {
            found = true;
            cout << "Find the employee: " << endl;
            cout << "ID: " << employees[i].id << endl;
            cout << "Name: " << employees[i].name << endl;
            cout << "Salary: " << employees[i].salary << endl;
            cout << "Number of years of work: " << employees[i].yearsOfWork << endl;
            cout << "Working hours this month: " << employees[i].hoursWorked << endl;
            break;
        }
        }
        if (!found) {
        cout << "The employee is not found. " << endl;
            }
        else
        	cout << "The employee is found. " << endl;
        
    }

void searchEmployeeBinary(Employee employees[], int numEmployees) {
    int searchId;
    cout << "---------------------------\n";
    cout << "Enter the employee ID you are looking for: ";
    cin >> searchId;

    int left = 0;
    int right = numEmployees - 1;
    bool found = false;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (employees[mid].id == searchId) {
            found = true;
            cout << "Find the employee:" << endl;
            cout << "ID: " << employees[mid].id << endl;
            cout << "Name: " << employees[mid].name << endl;
            cout << "Salary: " << employees[mid].salary << endl;
            cout << "Number of years of work: " << employees[mid].yearsOfWork << endl;
            cout << "Working hours this month: " << employees[mid].hoursWorked << endl;
            break;
        } else if (employees[mid].id < searchId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) 
        cout << "The employee has not been found. " << endl;
    
    else
    	cout << "The employee has been found. " << endl;
}

int main() {
    Employee employees[100]; 
    int numEmployees = 0;

    int choice;

    do {
        displayMenu(choice);
        cin >> choice;

        switch (choice) {
            case 1:
                hireEmployee(employees, numEmployees);
                break;
            case 2:
             int employeeId;
             cout << "---------------------------\n";
             cout << "Enter the ID of the employee you wish to fire: ";
             cin >> employeeId;
             fireEmployee(employeeId);
             break;
            case 3:
                int sortBy;
                cout << "Staff rank by:" << endl;
                cout << "1. Salary" << endl;
                cout << "2. Years of Work" << endl;
                cout << "3. Hours Worked" << endl;
                cout << "Choose the option: ";
                cin >> sortBy;
                sortEmployees(employees, numEmployees, sortBy);
                displayEmployees(employees, numEmployees);
                break;
            case 4:
                int searchOption;
                cout << "---------------------------\n";
                cout << "Employee search method: " << endl;
                cout << "1. Sequential search" << endl;
                cout << "2. Binary search" << endl;
                cout << "Choose the method: ";
                cin >> searchOption;
                if (searchOption == 1) {
                    searchEmployeeSequential(employees, numEmployees);
                } else if (searchOption == 2) {
                    searchEmployeeBinary(employees, numEmployees);
                } else {
                    cout << "Invalid option." << endl;
                }
                break;
            case 0:
                cout << "Thank you for using the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}