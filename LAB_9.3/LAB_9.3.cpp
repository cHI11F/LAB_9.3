#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

struct Employee {
    string lastName;
    string phoneNumber;
    string roomNumber;
};

string filename;

void addEmployee(map<string, Employee>& phoneBook) {
    Employee newEmployee;
    cout << "Enter last name: ";
    cin >> newEmployee.lastName;
    cout << "Enter phone number (two digits): ";
    cin >> newEmployee.phoneNumber;
    cout << "Enter room number: ";
    cin >> newEmployee.roomNumber;

    phoneBook[newEmployee.phoneNumber] = newEmployee;
}

void deleteEmployee(map<string, Employee>& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number to delete: ";
    cin >> phoneNumber;

    auto it = phoneBook.find(phoneNumber);
    if (it != phoneBook.end()) {
        phoneBook.erase(it);
        cout << "Employee with phone number " << phoneNumber << " deleted successfully." << endl;
    }
    else {
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }
}

void printEmployeeByPhoneNumber(const map<string, Employee>& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    auto it = phoneBook.find(phoneNumber);
    if (it != phoneBook.end()) {
        cout << "Last name: " << it->second.lastName << ", Room number: " << it->second.roomNumber << endl;
    }
    else {
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }
}

void printPhoneNumberByRoomNumber(const map<string, Employee>& phoneBook) {
    string roomNumber;
    cout << "Enter room number: ";
    cin >> roomNumber;

    for (const auto& entry : phoneBook) {
        if (entry.second.roomNumber == roomNumber) {
            cout << "Phone number: " << entry.first << endl;
            return;
        }
    }

    cout << "No employees found in room " << roomNumber << endl;
}

void printEmployeeByLastName(const map<string, Employee>& phoneBook) {
    string lastName;
    cout << "Enter last name: ";
    cin >> lastName;

    for (const auto& entry : phoneBook) {
        if (entry.second.lastName == lastName) {
            cout << "Phone number: " << entry.first << ", Room number: " << entry.second.roomNumber << endl;
            return;
        }
    }

    cout << "No employees found with last name " << lastName << endl;
}

void savePhoneBookToFile(const map<string, Employee>& phoneBook) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& entry : phoneBook) {
        fout << entry.second.lastName << " " << entry.first << " " << entry.second.roomNumber << endl;
    }

    cout << "Phone book has been saved to file: " << filename << endl;
    fout.close();
}

void readPhoneBookFromFile(map<string, Employee>& phoneBook) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    phoneBook.clear();

    Employee employee;
    string phoneNumber;
    while (fin >> employee.lastName >> phoneNumber >> employee.roomNumber) {
        phoneBook[phoneNumber] = employee;
    }

    cout << "Phone book has been read from file: " << filename << endl;
    fin.close();
}

int main() {
    map<string, Employee> phoneBook;

    cout << "Enter filename: ";
    getline(cin, filename);

    readPhoneBookFromFile(phoneBook);

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Delete employee" << endl;
        cout << "3. Print employee by phone number" << endl;
        cout << "4. Print phone number by room number" << endl;
        cout << "5. Print employee by last name" << endl;
        cout << "6. Save phone book to file" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            addEmployee(phoneBook);
            break;
        case 2:
            deleteEmployee(phoneBook);
            break;
        case 3:
            printEmployeeByPhoneNumber(phoneBook);
            break;
        case 4:
            printPhoneNumberByRoomNumber(phoneBook);
            break;
        case 5:
            printEmployeeByLastName(phoneBook);
            break;
        case 6:
            savePhoneBookToFile(phoneBook);
            break;
        case 7:
            cout << "Exiting program." << endl;
            savePhoneBookToFile(phoneBook);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
        }
    }

    return 0;
}
