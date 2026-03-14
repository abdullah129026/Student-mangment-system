#include"Attendance.h"
#include<iostream>  
#include<fstream>


Attendance::Attendance() {
    rollNumber= 0;
    totalClasses = 0;
    classesAttended = 0;
    attendancePercentage = 0.0;
}
//setters
void Attendance::setRollNumber(int rollNumber) {
    this->rollNumber = rollNumber;
}
void Attendance::setTotalClasses(int totalClasses) {
    this->totalClasses = totalClasses;
}
void Attendance::setClassesAttended(int classesAttended) {
    this->classesAttended = classesAttended;
}
//getters
int Attendance::getRollNumber() const {
    return rollNumber;
}
int Attendance::getTotalClasses() const {
    return totalClasses;
}
int Attendance::getClassesAttended() const {
    return classesAttended;
}
float Attendance::getAttendancePercentage() const {
    return attendancePercentage;
}

//Methods
void Attendance::markAttendance(int rollNumber)
{
    // First verify student exists
    ifstream studentFile("data/students.txt");
    if(!studentFile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return;
    }
    
    bool studentFound = false;
    int roll;
    string studName, studGender, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(studentFile >> roll >> delimiter 
                     >> studName >> delimiter 
                     >> studAge >> delimiter 
                     >> studGender >> delimiter 
                     >> studAddress >> delimiter 
                     >> studPhone)
    {
        if(roll == rollNumber)
        {
            studentFound = true;
            break;
        }
    }
    studentFile.close();
    
    if(!studentFound)
    {
        cout << "Student with roll number " << rollNumber << " not found!" << endl;
        return;
    }
    
    // Check if attendance record already exists
    ifstream attnFile("data/attendance.txt");
    if(attnFile.is_open())
    {
        int enrRoll, enrTotal, enrAttended;
        float enrPercentage;
        while(attnFile >> enrRoll >> delimiter >> enrTotal >> delimiter >> enrAttended >> delimiter >> enrPercentage)
        {
            if(enrRoll == rollNumber)
            {
                cout << "Attendance record already exists for this student!" << endl;
                attnFile.close();
                return;
            }
        }
        attnFile.close();
    }
    
    // Now mark attendance
    cout << "Enter total classes: ";
    cin >> totalClasses;
    cout << "Enter classes attended: ";
    cin >> classesAttended;
    
    setRollNumber(rollNumber);
    setTotalClasses(totalClasses);
    setClassesAttended(classesAttended);
    calculateAttendance();
    saveAttendanceToFile();
}

void Attendance::updateAttendance(int rollNumber)
{
    ifstream inFile("data/attendance.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening attendance file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_attendance.txt");
    bool found = false;
    
    int roll, total, attended;
    float percentage;
    char delimiter;
    
    while(inFile >> roll >> delimiter >> total >> delimiter >> attended >> delimiter >> percentage)
    {
        if(roll == rollNumber)
        {
            found = true;
            cout << "Enter updated classes attended: ";
            cin >> attended;
            
            cout << "Enter updated total classes: ";
            cin >> total;
            
            setRollNumber(rollNumber);
            setTotalClasses(total);
            setClassesAttended(attended);
            calculateAttendance();
            
            cout << "Attendance updated successfully!" << endl;
        }
        else
        {
            tempFile << roll << "|" << total << "|" << attended << "|" << percentage << endl;
        }
    }
    
    if(found)
    {
        tempFile << rollNumber << "|" << totalClasses << "|" << classesAttended << "|" << attendancePercentage << endl;
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/attendance.txt");
    rename("data/temp_attendance.txt", "data/attendance.txt");
    
    if(!found)
        cout << "Attendance record not found!" << endl;
}

void Attendance::calculateAttendance() {
    if(totalClasses > 0)
        attendancePercentage = (float)classesAttended / totalClasses * 100;
    else
        attendancePercentage = 0.0;
}

void Attendance::displayAttendance() const {
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Total Classes: " << totalClasses << endl;
    cout << "Classes Attended: " << classesAttended << endl;
    cout << "Attendance Percentage: " << attendancePercentage << "%" << endl;
}

void Attendance::saveAttendanceToFile()
{
    ofstream outFile("data/attendance.txt", ios::app);
    if(outFile.is_open())
    {
        outFile << rollNumber << "|" 
                << totalClasses << "|" 
                << classesAttended << "|" 
                << attendancePercentage << endl;
        outFile.close();
        cout << "Attendance saved successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}
