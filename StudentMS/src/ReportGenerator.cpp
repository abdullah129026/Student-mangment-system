#include "ReportGenerator.h"

void ReportGenerator::generateStudentReport(const Student& student) const
{
    cout << "\n==== Student Report ====" << endl;
    
    ofstream file("reports/student_report.txt", ios::app);
    if(file.is_open())
    {
        file << "\n===== Student Report =====" << endl;
        file << "Roll Number: " << student.getRollNumber() << endl;
        file << "Name: " << student.getName() << endl;
        file << "Age: " << student.getAge() << endl;
        file << "Gender: " << student.getGender() << endl;
        file << "Class ID: " << student.getClassID() << endl;
        file << "Phone Number: " << student.getPhoneNumber() << endl;
        file << "Address: " << student.getAddress() << endl;
        file << "==========================" << endl;
        file.close();
        cout << "Student report generated successfully!" << endl;
    }
    else
    {
        cout << "Unable to create report file!" << endl;
    }
}

void ReportGenerator::generateAttendanceReport(const Attendance& attendance) const
{
    cout << "\n==== Attendance Report ====" << endl;
    
    ofstream file("reports/attendance_report.txt", ios::app);
    if(file.is_open())
    {
        file << "\n===== Attendance Report =====" << endl;
        file << "Roll Number: " << attendance.getRollNumber() << endl;
        file << "Total Classes: " << attendance.getTotalClasses() << endl;
        file << "Classes Attended: " << attendance.getClassesAttended() << endl;
        file << "Attendance Percentage: " << attendance.getAttendancePercentage() << "%" << endl;
        file << "=============================" << endl;
        file.close();
        cout << "Attendance report generated successfully!" << endl;
    }
    else
    {
        cout << "Unable to create report file!" << endl;
    }
}

void ReportGenerator::generateResultReport(const Result& result) const
{
    cout << "\n==== Result Report ====" << endl;
    
    ofstream file("reports/result_report.txt", ios::app);
    if(file.is_open())
    {
        file << "\n===== Result Report =====" << endl;
        file << "Roll Number: " << result.getRollNumber() << endl;
        file << "Subject: " << result.getSubject() << endl;
        file << "Marks Obtained: " << result.getMarks() << endl;
        file << "Total Marks: " << result.getTotalMarks() << endl;
        file << "Percentage: " << result.getPercentage() << "%" << endl;
        file << "Grade: " << result.getGrade() << endl;
        file << "========================" << endl;
        file.close();
        cout << "Result report generated successfully!" << endl;
    }
    else
    {
        cout << "Unable to create report file!" << endl;
    }
}

void ReportGenerator::generateFeesReport(const Fees& fees) const
{
    cout << "\n==== Fees Report ====" << endl;
    
    ofstream file("reports/fees_report.txt", ios::app);
    if(file.is_open())
    {
        file << "\n===== Fees Report =====" << endl;
        file << "Roll Number: " << fees.getRollNumber() << endl;
        file << "Total Fees: " << fees.getTotalFees() << endl;
        file << "Paid Fees: " << fees.getPaidFees() << endl;
        file << "Remaining Fees: " << fees.getRemainingFees() << endl;
        file << "Payment Date: " << fees.getPaymentdate() << endl;
        file << "======================" << endl;
        file.close();
        cout << "Fees report generated successfully!" << endl;
    }
    else
    {
        cout << "Unable to create report file!" << endl;
    }
}

void ReportGenerator::generateFullReport(const Student& student,
                                        const Result& result,
                                        const Fees& fees,
                                        const Attendance& attendance) const
{
    cout << "\n========================================" << endl;
    cout << "     COMPLETE STUDENT REPORT CARD      " << endl;
    cout << "========================================" << endl;
    
    ofstream file("reports/full_report.txt", ios::app);
    if(file.is_open())
    {
        file << "\n\n========================================" << endl;
        file << "     COMPLETE STUDENT REPORT CARD      " << endl;
        file << "========================================" << endl;
        
        // Student Information
        file << "\n--- Student Information ---" << endl;
        file << "Roll Number: " << student.getRollNumber() << endl;
        file << "Name: " << student.getName() << endl;
        file << "Age: " << student.getAge() << " years" << endl;
        file << "Gender: " << student.getGender() << endl;
        file << "Class ID: " << student.getClassID() << endl;
        file << "Phone: " << student.getPhoneNumber() << endl;
        file << "Address: " << student.getAddress() << endl;
        
        // Academic Results
        file << "\n--- Academic Results ---" << endl;
        file << "Subject: " << result.getSubject() << endl;
        file << "Marks Obtained: " << result.getMarks() << endl;
        file << "Total Marks: " << result.getTotalMarks() << endl;
        file << "Percentage: " << result.getPercentage() << "%" << endl;
        file << "Grade: " << result.getGrade() << endl;
        
        // Attendance Record
        file << "\n--- Attendance Record ---" << endl;
        file << "Total Classes: " << attendance.getTotalClasses() << endl;
        file << "Classes Attended: " << attendance.getClassesAttended() << endl;
        file << "Attendance: " << attendance.getAttendancePercentage() << "%" << endl;
        
        // Fee Status
        file << "\n--- Fee Status ---" << endl;
        file << "Total Fees: " << fees.getTotalFees() << endl;
        file << "Paid Fees: " << fees.getPaidFees() << endl;
        file << "Remaining Fees: " << fees.getRemainingFees() << endl;
        file << "Last Payment Date: " << fees.getPaymentdate() << endl;
        
        file << "\n========================================" << endl;
        file << "         End of Report Card            " << endl;
        file << "========================================" << endl;
        file << "\n\n";
        
        file.close();
        
        cout << "\nFull report card generated successfully!" << endl;
        cout << "Report saved to: reports/full_report.txt" << endl;
    }
    else
    {
        cout << "Unable to create report file!" << endl;
    }
}
