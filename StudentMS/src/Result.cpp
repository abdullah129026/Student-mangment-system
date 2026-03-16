#include "Result.h"

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

void Result::displayResult(int rollNumber) const
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
            cout << "-----------------" << endl;
        }
    }
    
    resultfile.close();
    
    if(!resultFound)
    {
        cout << "No result found for roll number " << rollNumber << endl;
    }
}


//update result
void Result::updateResult(int rollNumber)
{
    //verify if there is a student to update
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
    
    //check if result exists
    ifstream resultfile("data/result.txt");
    if(!resultfile.is_open())
    {
        cout << "No result record found to update!" << endl;
        return;
    }
    
    bool resultExists = false;
    int stroll;
    string sub;
    int m, total;
    float perc;
    string grd;
    
    while(resultfile >> stroll >> delimiter >> sub >> delimiter >> m >> delimiter >> total >> delimiter >> perc >> delimiter >> grd)
    {
        if(stroll == rollNumber)
        {
            resultExists = true;
            break;
        }
    }
    resultfile.close();
    
    if(!resultExists)
    {
        cout << "No result found for roll number " << rollNumber << "!" << endl;
        return;
    }
    
    //there is a student and result to update
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
    
    //read all results and update the matching one
    ifstream inFile("data/result.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening result file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_result.txt");
    
    while(inFile >> stroll >> delimiter >> sub >> delimiter >> m >> delimiter >> total >> delimiter >> perc >> delimiter >> grd)
    {
        if(stroll == rollNumber)
        {
            tempFile << rollNumber << "|" 
                     << subject << "|" 
                     << marks << "|" 
                     << totalMarks << "|" 
                     << percentage << "|" 
                     << grade << endl;
            cout << "Result updated successfully!" << endl;
        }
        else
        {
            tempFile << stroll << "|" << sub << "|" << m << "|" << total << "|" << perc << "|" << grd << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/result.txt");
    rename("data/temp_result.txt", "data/result.txt");
}
