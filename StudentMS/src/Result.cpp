#include "Result.h"
#include <vector>

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
    string line;
    
    while(getline(studentfile, line))
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
            if(roll == rollNumber)
            {
                studentFound = true;
                break;
            }
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
        while(getline(resultfile, line))
        {
            if(line.empty()) continue;
            
            size_t pipePos = line.find('|');
            if(pipePos != string::npos) {
                int stroll = stoi(line.substr(0, pipePos));
                if(stroll == rollNumber)
                {
                    cout << "Result already exists for roll number " << rollNumber << endl;
                    resultfile.close();
                    return;
                }
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
    string line;
    
    while(getline(studentfile, line))
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
            if(roll == rollNumber)
            {
                studentFound = true;
                break;
            }
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
    
    cout << "\n==== Result for Roll Number " << rollNumber << " ====" << endl;
    
    while(getline(resultfile, line))
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
        
        if(fields.size() >= 6) {
            int stroll = stoi(fields[0]);
            if(stroll == rollNumber)
            {
                resultFound = true;
                cout << "\nSubject: " << fields[1] << endl;
                cout << "Marks Obtained: " << fields[2] << endl;
                cout << "Total Marks: " << fields[3] << endl;
                cout << "Percentage: " << fields[4] << "%" << endl;
                cout << "Grade: " << fields[5] << endl;
                cout << "-----------------" << endl;
            }
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
    string line;
    
    while(getline(studentfile, line))
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
            if(roll == rollNumber)
            {
                studentFound = true;
                break;
            }
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
    
    while(getline(resultfile, line))
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
            int stroll = stoi(fields[0]);
            if(stroll == rollNumber)
            {
                resultExists = true;
                break;
            }
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
        
        if(fields.size() >= 6) {
            int stroll = stoi(fields[0]);
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
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/result.txt");
    rename("data/temp_result.txt", "data/result.txt");
}
