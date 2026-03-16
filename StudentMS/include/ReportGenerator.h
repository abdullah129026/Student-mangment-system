#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "Student.h"
#include "Result.h"
#include "Fees.h"
#include "Attendance.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

class ReportGenerator { 
    public:
    void generateStudentReport(const Student& student) const;
    void generateAttendanceReport(const Attendance& attendance) const;
    void generateResultReport(const Result& result) const;
    void generateFeesReport(const Fees& fees) const;

    //full report
    void generateFullReport(const Student& student,
        const Result& result,
        const Fees& fees,
        const Attendance& attendance) const;
};

#endif
