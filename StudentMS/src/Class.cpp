#include "Class.h"
#include "Student.h"
#include <vector>

Schoolclass::Schoolclass()
{
    classID = "";
    className = "";
    section = "";
    classTeacher = "";
}

Schoolclass::Schoolclass(string classID, string className, string section, string classTeacher)
{
    this->classID = classID;
    this->className = className;
    this->section = section;
    this->classTeacher = classTeacher;
}

void Schoolclass::addClass()
{
    cout << "Enter class ID: ";
    cin >> classID;
    cout << "Enter class name: ";
    cin >> className;
    cout << "Enter section: ";
    cin >> section;
    cout << "Enter class teacher: ";
    cin.ignore();
    getline(cin, classTeacher);
    
    ofstream outFile("data/classes.txt", ios::app);
    if(outFile.is_open())
    {
        outFile << classID << "|" << className << "|" << section << "|" << classTeacher << endl;
        outFile.close();
        cout << "Class added successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}
void Schoolclass::updateClass(string classToUpdate)
{
    ifstream inFile("data/classes.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_classes.txt");
    bool found = false;
    string line;
    
    while(getline(inFile, line))
    {
        if(line.empty()) continue;
        
        // Parse first field (class ID)
        size_t pipePos = line.find('|');
        if(pipePos != string::npos)
        {
            string clsID = line.substr(0, pipePos);
            
            if(clsID == classToUpdate)
            {
                found = true;
                cout << "Enter updated details for class " << classToUpdate << ":" << endl;
                
                string newID, newName, newSection, newTeacher;
                
                cout << "Enter class ID: ";
                cin >> newID;
                cout << "Enter class name: ";
                cin >> newName;
                cout << "Enter section: ";
                cin >> newSection;
                cout << "Enter class teacher: ";
                cin.ignore();
                getline(cin, newTeacher);
                
                // Write updated record
                tempFile << newID << "|" << newName << "|" << newSection << "|" << newTeacher << endl;
                cout << "Class updated successfully!" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/classes.txt");
    rename("data/temp_classes.txt", "data/classes.txt");
    
    if(!found)
        cout << "Class not found!" << endl;
}

void Schoolclass::displayClassinfo() const
{
    cout << "Class ID: " << classID << endl;
    cout << "Class Name: " << className << endl;
    cout << "Section: " << section << endl;
    cout << "Class Teacher: " << classTeacher << endl;
}

void Schoolclass::addStudentToClass(int rollNumber, string classID)
{
    // First verify student exists in students.txt
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
        
        size_t pipePos = line.find('|');
        if(pipePos != string::npos)
        {
            int roll = stoi(line.substr(0, pipePos));
            if(roll == rollNumber)
            {
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
    
    // Check if student is already in this class
    ifstream classFile("data/classes.txt");
    if(!classFile.is_open())
    {
        cout << "Error opening classes file!" << endl;
        return;
    }
    
    bool classFound = false;
    while(getline(classFile, line))
    {
        if(line.empty()) continue;
        
        size_t pipePos = line.find('|');
        if(pipePos != string::npos)
        {
            string clsID = line.substr(0, pipePos);
            if(clsID == classID)
            {
                classFound = true;
                break;
            }
        }
    }
    classFile.close();
    
    if(classFound)
    {
        // Check if student already enrolled
        ifstream enrollFile("data/enrollments.txt");
        if(enrollFile.is_open())
        {
            while(getline(enrollFile, line))
            {
                if(line.empty()) continue;
                
                size_t pipePos = line.find('|');
                if(pipePos != string::npos)
                {
                    int enrRoll = stoi(line.substr(0, pipePos));
                    string enrClassID = line.substr(pipePos + 1);
                    
                    if(enrRoll == rollNumber && enrClassID == classID)
                    {
                        cout << "Student is already enrolled in this class!" << endl;
                        enrollFile.close();
                        return;
                    }
                }
            }
            enrollFile.close();
        }
    }
    
    // Add student to class (create enrollment record)
    ofstream enrollFile("data/enrollments.txt", ios::app);
    if(enrollFile.is_open())
    {
        enrollFile << rollNumber << "|" << classID << endl;
        enrollFile.close();
        cout << "Student added to class successfully!" << endl;
    }
    else
    {
        cout << "Error opening enrollments file!" << endl;
    }
}

void Schoolclass::removeStudentFromClass(int rollNumber, string classID)
{
    // Remove from enrollments
    ifstream enrollFile("data/enrollments.txt");
    if(!enrollFile.is_open())
    {
        cout << "No enrollments found!" << endl;
        return;
    }
    
    ofstream tempEnroll("data/temp_enrollments.txt");
    bool foundInClass = false;
    
    int roll;
    string clsID;
    char delimiter;
    
    while(enrollFile >> roll >> delimiter >> clsID)
    {
        if(roll == rollNumber && clsID == classID)
        {
            foundInClass = true;
            cout << "Student removed from class successfully!" << endl;
        }
        else
        {
            tempEnroll << roll << "|" << clsID << endl;
        }
    }
    
    enrollFile.close();
    tempEnroll.close();
    
    remove("data/enrollments.txt");
    rename("data/temp_enrollments.txt", "data/enrollments.txt");
    
    if(!foundInClass)
    {
        cout << "Student not found in this class!" << endl;
        return;
    }
    
    // Delete student from students.txt as well
    ifstream studentFile("data/students.txt");
    if(!studentFile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return;
    }
    
    ofstream tempStudent("data/temp_students.txt");
    bool studentDeleted = false;
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
            
            if(roll == rollNumber)
            {
                studentDeleted = true;
                cout << "Student deleted from system!" << endl;
            }
            else
            {
                tempStudent << line << endl;
            }
        }
    }
    
    studentFile.close();
    tempStudent.close();
    
    remove("data/students.txt");
    rename("data/temp_students.txt", "data/students.txt");

}

void Schoolclass::displayClassStudents(string classID)
{
    ifstream enrollFile("data/enrollments.txt");
    if(!enrollFile.is_open())
    {
        cout << "No students enrolled in any class yet." << endl;
        return;
    }
    
    vector<int> enrolledRolls;
    string line;
    char delimiter;
    
    while(getline(enrollFile, line))
    {
        if(line.empty()) continue;
        
        size_t pipePos = line.find('|');
        if(pipePos != string::npos) {
            int roll = stoi(line.substr(0, pipePos));
            string clsID = line.substr(pipePos + 1);
            
            if(clsID == classID)
            {
                enrolledRolls.push_back(roll);
            }
        }
    }
    enrollFile.close();
    
    if(enrolledRolls.empty())
    {
        cout << "No students enrolled in class " << classID << endl;
        return;
    }
    
    cout << "\n=== Students Enrolled in Class " << classID << " ===" << endl;
    
    ifstream studentFile("data/students.txt");
    if(!studentFile.is_open())
    {
        cout << "Error opening students file!" << endl;
        return;
    }
    
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
        
        if(fields.size() >= 7) {
            int roll = stoi(fields[0]);
            
            for(size_t i = 0; i < enrolledRolls.size(); i++)
            {
                if(roll == enrolledRolls[i])
                {
                    cout << "\nRoll Number: " << roll << endl;
                    cout << "Name: " << fields[1] << endl;
                    cout << "Age: " << fields[2] << endl;
                    cout << "Gender: " << fields[3] << endl;
                    cout << "Address: " << fields[4] << endl;
                    cout << "Phone: " << fields[5] << endl;
                    break;
                }
            }
        }
    }
    
    studentFile.close();
}

//getters
string Schoolclass::getClassID() const
{
    return classID;
}

string Schoolclass::getClassName() const
{
    return className;
}

string Schoolclass::getSection() const
{
    return section;
}

string Schoolclass::getClassTeacher() const
{
    return classTeacher;
}

