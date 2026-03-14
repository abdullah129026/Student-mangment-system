#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string>
#include <fstream>

using namespace std;

class Student
{
private:
    int rollNumber;
    string name;
    int age; 
    string gender;
    string classID;
    string address;
    string phoneNumber;

public:
    Student();
    Student(int rollNumber, string name, int age, string gender, string classID, string address, string phoneNumber);


    //setters
    void setStudentDetails(int rollNumber, string name, int age, string gender, string classID, string address, string phoneNumber);
    

    //getters

    int getRollNumber() const;
    string getName() const;
    int getAge() const;
    string getGender() const;
    string getClassID() const;
    string getAddress() const;
    string getPhoneNumber() const;    
    
    //methods
    void addStudent();
    void deleteStudent(int rollNumber);
    void searchStudent(int rollNumber);
    void displayStudent() const;
    void updateStudent(int rollNumber);



};

#endif
