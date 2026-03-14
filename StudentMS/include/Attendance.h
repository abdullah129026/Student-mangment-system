#ifndef ATTENDANCE_H
#define ATTENDANCE_H


#include"Student.h"
#include<iostream>
#include<fstream>
#include<string>


using namespace std;

class Attendance {
private:
    int rollNumber;
    int totalClasses;
    int classesAttended;
    float attendancePercentage;
public:
    Attendance();

    //setters
    void setRollNumber(int rollNumber);
    void setTotalClasses(int totalClasses);
    void setClassesAttended(int classesAttended);
    //getters
    int getRollNumber() const;
    int getTotalClasses() const;
    int getClassesAttended() const;
    float getAttendancePercentage() const;
    //methods
    void markAttendance(int rollNumber);
    void updateAttendance(int rollNumber);
    void displayAttendance() const;
    void calculateAttendance();
    void saveAttendanceToFile();

};


#endif