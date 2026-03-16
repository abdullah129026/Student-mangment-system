#include <iostream>
#include "Student.h"
#include "Attendance.h"
#include "Result.h"
#include "Fees.h"
#include "Class.h"
#include "ReportGenerator.h"

using namespace std;

int main() {
    int choice;
    
    while (true) {
        cout << "\n========================================" << endl;
        cout << "     STUDENT MANAGEMENT SYSTEM (SMS)    " << endl;
        cout << "========================================" << endl;
        cout << "1. Student Management" << endl;
        cout << "2. Attendance Management" << endl;
        cout << "3. Result Management" << endl;
        cout << "4. Fees Management" << endl;
        cout << "5. Class Management" << endl;
        cout << "6. Generate Reports" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int subChoice;
                cout << "\n--- Student Management ---" << endl;
                cout << "1. Add Student" << endl;
                cout << "2. Search Student" << endl;
                cout << "3. Update Student" << endl;
                cout << "4. Delete Student" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                Student student;
                if (subChoice == 1) {
                    student.addStudent();
                } else if (subChoice == 2) {
                    int roll;
                    cout << "Enter roll number to search: ";
                    cin >> roll;
                    student.searchStudent(roll);
                } else if (subChoice == 3) {
                    int roll;
                    cout << "Enter roll number to update: ";
                    cin >> roll;
                    student.updateStudent(roll);
                } else if (subChoice == 4) {
                    int roll;
                    cout << "Enter roll number to delete: ";
                    cin >> roll;
                    student.deleteStudent(roll);
                }
                break;
            }
            
            case 2: {
                int subChoice;
                cout << "\n--- Attendance Management ---" << endl;
                cout << "1. Mark Attendance" << endl;
                cout << "2. Update Attendance" << endl;
                cout << "3. Display Attendance" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                Attendance attendance;
                if (subChoice == 1) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    attendance.markAttendance(roll);
                } else if (subChoice == 2) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    attendance.updateAttendance(roll);
                } else if (subChoice == 3) {
                    // Display all attendance records
                    cout << "\n=== All Attendance Records ===" << endl;
                    ifstream file("data/attendance.txt");
                    if (file.is_open()) {
                        int roll, total, attended;
                        float percentage;
                        char delimiter;
                        while (file >> roll >> delimiter >> total >> delimiter >> attended >> delimiter >> percentage) {
                            cout << "\nRoll: " << roll << ", Total: " << total 
                                 << ", Attended: " << attended << ", Percentage: " 
                                 << percentage << "%" << endl;
                        }
                        file.close();
                    } else {
                        cout << "No attendance records found!" << endl;
                    }
                }
                break;
            }
            
            case 3: {
                int subChoice;
                cout << "\n--- Result Management ---" << endl;
                cout << "1. Add Result" << endl;
                cout << "2. Display Result" << endl;
                cout << "3. Update Result" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                Result result;
                if (subChoice == 1) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    result.addResult(roll);
                } else if (subChoice == 2) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    result.displayResult(roll);
                } else if (subChoice == 3) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    result.updateResult(roll);
                }
                break;
            }
            
            case 4: {
                int subChoice;
                cout << "\n--- Fees Management ---" << endl;
                cout << "1. Enter Fee Record" << endl;
                cout << "2. Display Fee Records" << endl;
                cout << "3. Pay Fees" << endl;
                cout << "4. Update Fee Record" << endl;
                cout << "5. Delete Fee Record" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                Fees fees;
                if (subChoice == 1) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    fees.enterfeerecord(roll);
                } else if (subChoice == 2) {
                    fees.displayfeerecord();
                } else if (subChoice == 3) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    fees.payfees(roll);
                } else if (subChoice == 4) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    fees.updatefeerecord(roll);
                } else if (subChoice == 5) {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    fees.deletefeerecord(roll);
                }
                break;
            }
            
            case 5: {
                int subChoice;
                cout << "\n--- Class Management ---" << endl;
                cout << "1. Add Class" << endl;
                cout << "2. Update Class" << endl;
                cout << "3. Display Class Info" << endl;
                cout << "4. Add Student to Class" << endl;
                cout << "5. Remove Student from Class" << endl;
                cout << "6. Display Class Students" << endl;
                cout << "Enter choice: ";
                cin >> subChoice;
                
                Schoolclass schoolClass;
                if (subChoice == 1) {
                    schoolClass.addClass();
                } else if (subChoice == 2) {
                    string classId;
                    cout << "Enter class ID to update: ";
                    cin >> classId;
                    schoolClass.updateClass(classId);
                } else if (subChoice == 3) {
                    // Display all classes
                    ifstream file("data/classes.txt");
                    if (file.is_open()) {
                        string id, name, section, teacher;
                        char delimiter;
                        while (file >> id >> delimiter >> name >> delimiter >> section >> delimiter >> teacher) {
                            cout << "\nClass ID: " << id << ", Name: " << name 
                                 << ", Section: " << section << ", Teacher: " << teacher << endl;
                        }
                        file.close();
                    } else {
                        cout << "No classes found!" << endl;
                    }
                } else if (subChoice == 4) {
                    int roll;
                    string classId;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    cout << "Enter class ID: ";
                    cin >> classId;
                    schoolClass.addStudentToClass(roll, classId);
                } else if (subChoice == 5) {
                    int roll;
                    string classId;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    cout << "Enter class ID: ";
                    cin >> classId;
                    schoolClass.removeStudentFromClass(roll, classId);
                } else if (subChoice == 6) {
                    string classId;
                    cout << "Enter class ID: ";
                    cin >> classId;
                    schoolClass.displayClassStudents(classId);
                }
                break;
            }
            
            case 6: {
                cout << "\n--- Report Generation ---" << endl;
                cout << "Reports are auto-generated when you perform operations." << endl;
                cout << "Check the 'reports' folder for generated reports." << endl;
                break;
            }
            
            case 0:
                cout << "Exiting... Thank you for using SMS!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
