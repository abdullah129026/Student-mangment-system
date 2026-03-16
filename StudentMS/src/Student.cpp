#include"Student.h"
#include <sstream>
#include <vector>

Student::Student() {
    rollNumber = 0;
    name = "";
    age = 0;
    gender = "";
    classID = "";
    address = "";
    phoneNumber = "";
}
Student::Student(int rollNumber, string name, int age, string gender, string classID, string address, string phoneNumber) {
    this->rollNumber = rollNumber;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->classID = classID;
    this->address = address;
    this->phoneNumber = phoneNumber;
}
//setters

void Student::setStudentDetails(int rollNumber, string name, int age, string gender, string classID, string address, string phoneNumber) {
    this->rollNumber = rollNumber;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->classID = classID;
    this->address = address;
    this->phoneNumber = phoneNumber;
}
//getters
int Student::getRollNumber() const {
    return rollNumber;
}
string Student::getName() const {
    return name;
}
int Student::getAge() const {
    return age;
}
string Student::getGender() const {
    return gender;
}
string Student::getClassID() const {
    return classID;
}
string Student::getAddress() const {
    return address;
}
string Student::getPhoneNumber() const {
    return phoneNumber;
}

void Student::displayStudent() const
{
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Class ID: " << classID << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phoneNumber << endl;
}

//Methods
void Student::addStudent()
{
    cout << "Enter roll number: ";
    cin >> rollNumber;
    cin.ignore(); 
    
    cout << "Enter name: ";
    getline(cin, name);
    
    cout << "Enter age: ";
    cin >> age;
    cin.ignore();
    
    cout << "Enter gender: ";
    getline(cin, gender);
    
    cout << "Enter class ID: ";
    getline(cin, classID);
    
    cout << "Enter address: ";
    getline(cin, address);
    
    cout << "Enter phone number: ";
    getline(cin, phoneNumber);
    
    // Write to text file
    ofstream outFile("data/students.txt", ios::app);
    if(outFile.is_open())
    {
        outFile << rollNumber << "|" 
                << name << "|" 
                << age << "|" 
                << gender << "|" 
                << classID << "|" 
                << address << "|" 
                << phoneNumber << endl;
        
        outFile.close();
        cout << "Student added successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}
void Student::deleteStudent(int rollToDelete)
{
    ifstream inFile("data/students.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_students.txt");
    bool found = false;
    string line;
    
    while(getline(inFile, line))
    {
        if(line.empty()) continue;
        
        // Parse the first field (roll number)
        size_t pipePos = line.find('|');
        if(pipePos != string::npos)
        {
            int roll = stoi(line.substr(0, pipePos));
            
            if(roll == rollToDelete)
            {
                found = true;
                cout << "Student deleted successfully!" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/students.txt");
    rename("data/temp_students.txt", "data/students.txt");
    
    if(!found)
        cout << "Student not found!" << endl;
}
void Student::searchStudent(int roll)
{
    ifstream file("data/students.txt");
    if(!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    string line;
    
    while(getline(file, line))
    {
        if(line.empty()) continue;
        
        // Extract fields manually by splitting on |
        vector<string> fields;
        size_t start = 0;
        size_t end = line.find('|');
        
        while(end != string::npos) {
            fields.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find('|', start);
        }
        fields.push_back(line.substr(start)); // Add last field
        
        // Check if we have all 7 fields and roll matches
        if(fields.size() >= 7) {
            int storedRoll = stoi(fields[0]);
            if(storedRoll == roll) {
                cout << "\nStudent Found\n";
                cout << "Roll Number: " << fields[0] << endl;
                cout << "Name: " << fields[1] << endl;
                cout << "Age: " << fields[2] << endl;
                cout << "Gender: " << fields[3] << endl;
                cout << "Class ID: " << fields[4] << endl;
                cout << "Address: " << fields[5] << endl;
                cout << "Phone: " << fields[6] << endl;
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        cout << "Student not found\n";
    }

    file.close();
}
void Student::updateStudent(int rollToUpdate)
{
    ifstream inFile("data/students.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_students.txt");
    bool found = false;
    string line;
    
    while(getline(inFile, line))
    {
        if(line.empty()) continue;
        
        // Parse the line
        size_t pipePos = line.find('|');
        if(pipePos != string::npos)
        {
            int roll = stoi(line.substr(0, pipePos));
            
            if(roll == rollToUpdate)
            {
                found = true;
                cout << "Enter new details for roll number " << roll << ":" << endl;
                
                // Get new values
                string newName, newGender, newClassID, newAddress, newPhone;
                int newAge;
                
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, newName);
                
                cout << "Enter age: ";
                cin >> newAge;
                cin.ignore();
                
                cout << "Enter gender: ";
                getline(cin, newGender);
                
                cout << "Enter class ID: ";
                getline(cin, newClassID);
                
                cout << "Enter address: ";
                getline(cin, newAddress);
                
                cout << "Enter phone number: ";
                getline(cin, newPhone);
                
                // Write updated record
                tempFile << roll << "|" << newName << "|" << newAge << "|" 
                         << newGender << "|" << newClassID << "|" << newAddress << "|" 
                         << newPhone << endl;
                
                cout << "Student updated successfully!" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/students.txt");
    rename("data/temp_students.txt", "data/students.txt");
    
    if(!found)
        cout << "Student not found!" << endl;
}
