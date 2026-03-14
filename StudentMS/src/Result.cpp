#include "Result.h"

Result::Result() {
    rollNumber = 0;
    subject = "";
    totalsubjects = 0;
    marks = 0;
    totalMarks = 0;
    grade = "";
    percentage = 0.0;
}

//setters
void Result::setRollNumber(int roll) {
    rollNumber = roll;
}

void Result::setSubject(string sub) {
    subject = sub;
}

void Result::setMarks(int m) {
    marks = m;
}

void Result::setTotalSubjects(int totalsub) {
    totalsubjects = totalsub;
}

void Result::setTotalMarks(int total) {
    totalMarks = total;
}

//getters
int Result::getRollNumber() const {
    return rollNumber;
}

string Result::getSubject() const {
    return subject;
}

int Result::getMarks() const {
    return marks;
}

int Result::getTotalSubjects() const {
    return totalsubjects;
}

int Result::getTotalMarks() const {
    return totalMarks;
}

float Result::getPercentage() const {
    return percentage;
}

string Result::getGrade() const {
    return grade;
}

void Result::calculatePercentage() {
    if(totalsubjects > 0)
        percentage = ((float)totalMarks / totalsubjects) * 100;
    else
        percentage = 0.0;
}

void Result::calculateGrade() {
    if(percentage >= 90)
        grade = "A+";
    else if(percentage >= 80)
        grade = "A";
    else if(percentage >= 70)
        grade = "B";
    else if(percentage >= 60)
        grade = "C";
    else if(percentage >= 50)
        grade = "D";
    else
        grade = "F";
}

//Methods

void Result::addResult(int rollNumber)
{
    //verify student exists
    ifstream studentfile("data/students.txt");
    if(!studentfile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return;
    }
    
    bool studentFound = false;
    int roll;
    string studName, studGender, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(studentfile >> roll >> delimiter 
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
    studentfile.close();
    
    if(!studentFound)
    {
        cout << "Student with roll number " << rollNumber << " not found!" << endl;
        return;
    }
    
    //result already exists
    ifstream resultfile("data/result.txt");
    if(resultfile.is_open())
    {
        int stroll;
        string sub;
        int m, total;
        float perc;
        string grd;
        while(resultfile >> stroll >> delimiter >> sub >> delimiter >> m >> delimiter >> total >> delimiter >> perc >> delimiter >> grd)
        {
            if(stroll == rollNumber)
            {
                cout << "Result already exists for roll number " << rollNumber << endl;
                resultfile.close();
                return;
            }
        }
        resultfile.close();
    }
    
    //result donot exists
    int totalsubjects;
    cout << "Enter total subjects: ";
    cin >> totalsubjects;
    
    totalMarks = 0;
    for(int i = 0; i < totalsubjects; i++)
    {
        cout << "Enter subject " << (i+1) << ": ";
        cin >> subject;
        cout << "Enter marks for " << subject << ": ";
        cin >> marks;
        totalMarks += marks;
    }
    
    calculatePercentage();
    calculateGrade();
    
    ofstream outfile("data/result.txt", ios::app);
    if(outfile.is_open())
    {
        outfile << rollNumber << "|" 
                << subject << "|" 
                << marks << "|" 
                << totalMarks << "|" 
                << percentage << "|" 
                << grade << endl;
        outfile.close();
        cout << "Result added successfully!" << endl;
    }
    else
    {
        cout << "Error opening result file!" << endl;
    }
}

//show result

void Result::displayResult(int rollNumber)
{
    //verify student exists
    ifstream studentfile("data/students.txt");
    if(!studentfile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return;
    }
    
    bool studentFound = false;
    int roll;
    string studName, studGender, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(studentfile >> roll >> delimiter 
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
    studentfile.close();
    
    if(!studentFound)
    {
        cout << "Student with roll number " << rollNumber << " not found!" << endl;
        return;
    }
    
    //result exists
    ifstream resultfile("data/result.txt");
    if(!resultfile.is_open())
    {
        cout << "Error opening results file!" << endl;
        return;
    }
    
    bool resultFound = false;
    int stroll;
    string sub;
    int m, total;
    float perc;
    string grd;
    
    cout << "\n==== Result for Roll Number " << rollNumber << " ====" << endl;
    
    while(resultfile >> stroll >> delimiter >> sub >> delimiter >> m >> delimiter >> total >> delimiter >> perc >> delimiter >> grd)
    {
        if(stroll == rollNumber)
        {
            resultFound = true;
            cout << "\nSubject: " << sub << endl;
            cout << "Marks Obtained: " << m << endl;
            cout << "Total Marks: " << total << endl;
            cout << "Percentage: " << perc << "%" << endl;
            cout << "Grade: " << grd << endl;
            cout << "--------------------" << endl;
        }
    }
    
    resultfile.close();
    
    if(!resultFound)
    {
        cout << "No result found for roll number " << rollNumber << endl;
    }
}
