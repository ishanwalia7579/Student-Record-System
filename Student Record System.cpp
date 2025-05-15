
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent() {
    Student s;
    ofstream outFile("students.dat", ios::binary | ios::app);

    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Marks: ";
    cin >> s.marks;

    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();
    cout << "Student added successfully!\n";
}

void viewStudents() {
    Student s;
    ifstream inFile("students.dat", ios::binary);

    cout << "\n--- Student Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "Roll No: " << s.rollNo << "\n";
        cout << "Name: " << s.name << "\n";
        cout << "Marks: " << s.marks << "\n";
        cout << "-----------------------\n";
    }
    inFile.close();
}

void updateStudent() {
    int roll;
    bool found = false;
    Student s;

    fstream file("students.dat", ios::binary | ios::in | ios::out);
    cout << "Enter Roll No to update: ";
    cin >> roll;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Enter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);
            cout << "Enter New Marks: ";
            cin >> s.marks;

            file.seekp(-sizeof(s), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));
            found = true;
            cout << "Record updated successfully!\n";
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Student not found!\n";
}

void deleteStudent() {
    int roll;
    bool found = false;
    Student s;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    cout << "Enter Roll No to delete: ";
    cin >> roll;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
