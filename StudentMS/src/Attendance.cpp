#include"Attendance.h"
#include<iostream>  
#include<fstream>
#include<vector>

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
    string line;
    
    while(getline(studentFile, line))
    {
        if(line.empty()) continue;
        
        vector<string> fields;
        size_t start = 0;
        size_t end = line.find('|');
        
        while(end != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find('|', start);
        }
        fields.push_back(line.substr(start));
        
        if(fields.size() >= 1) {
            int roll = stoi(fields[0]);
            if(roll == rollNumber) {
                studentFound = true;
                break;
            }
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
        while(getline(attnFile, line))
        {
            if(line.empty()) continue;
            
            size_t pipePos = line.find('|');
            if(pipePos != string::npos) {
                int enrRoll = stoi(line.substr(0, pipePos));
                if(enrRoll == rollNumber)
                {
                    cout << "Attendance record already exists for this student!" << endl;
                    attnFile.close();
                    return;
                }
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
    string line;
    
    while(getline(inFile, line))
    {
        if(line.empty()) continue;
        
        vector<string> fields;
        size_t start = 0;
        size_t end = line.find('|');
        
        while(end != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find('|', start);
        }
        fields.push_back(line.substr(start));
        
        if(fields.size() >= 4) {
            int roll = stoi(fields[0]);
            int total = stoi(fields[1]);
            int attended = stoi(fields[2]);
            
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
                tempFile << line << endl;
            }
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
