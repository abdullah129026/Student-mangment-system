#ifndef CLASS_H
#define CLASS_H

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Student.h"

using namespace std;

class Schoolclass
{
    private:
    string classID;
    string className;
    string section;
    string classTeacher;

    vector<Student> students;
    public:
    //constructor
    Schoolclass();
    Schoolclass(string classID, string className, string section, string classTeacher);
    
    //class methods
    void addClass();
    void updateClass(string classID);
    void displayClassinfo() const;
    
    //Student management in class
    void addStudentToClass(int rollNumber, string classID);
    void removeStudentFromClass(int rollNumber, string classID);
    void displayClassStudents(string classID);
    
    //getters
    string getClassID() const;
    string getClassName() const;
    string getSection() const;
    string getClassTeacher() const;
};

#endif
