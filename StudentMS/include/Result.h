#ifndef RESULT_H
#define RESULT_H

#include "Student.h"

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Result {
    private:
    int rollNumber;
    string subject;
    int totalsubjects;
    int marks;
    int totalMarks=0;
    string grade;
    float percentage;
        
    public:
    
    // Default constructor
    Result() {}
    //setters
    void setRollNumber(int roll);
    void setSubject(string sub);
    void setMarks(int m);
    void setTotalSubjects(int totalsub);
    void setTotalMarks(int total);

    //Getters
    int getRollNumber() const;
    void getSubject() const;
    int getMarks() const;
    int getTotalSubjects() const;
    int getTotalMarks() const;
    void getGrade() const;
    void getPercentage() const;

    //  methods

    void addResult(int rollNumber);
    void displayResult(int rollNumber) const;
    void updateResult(int rollNumber);
    void calculatePercentage();
    void calculateGrade();
}

#endif
