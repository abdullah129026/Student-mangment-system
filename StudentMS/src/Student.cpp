#include"Student.h"

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
    
    int roll;
    string studName, studGender, studClassID, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(inFile >> roll >> delimiter 
                  >> studName >> delimiter 
                  >> studAge >> delimiter 
                  >> studGender >> delimiter 
                  >> studClassID >> delimiter 
                  >> studAddress >> delimiter 
                  >> studPhone)
    {
        if(roll == rollToDelete)
        {
            found = true;
            cout << "Student deleted successfully!" << endl;
        }
        else
        {
            tempFile << roll << "|" 
                     << studName << "|" 
                     << studAge << "|" 
                     << studGender << "|" 
                     << studClassID << "|" 
                     << studAddress << "|" 
                     << studPhone << endl;
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
    
    int storedRoll;
    string studName, studGender, studClassID, studAddress, studPhone;
    int studAge;
    char delimiter;

    while(file >> storedRoll >> delimiter 
                 >> studName >> delimiter 
                 >> studAge >> delimiter 
                 >> studGender >> delimiter 
                 >> studClassID >> delimiter 
                 >> studAddress >> delimiter 
                 >> studPhone)
    {
        if(storedRoll == roll )
        {
            cout << "\nStudent Found\n";
            cout << "Roll Number: " << storedRoll << endl;
            cout << "Name: " << studName << endl;
            cout << "Age: " << studAge << endl;
            cout << "Gender: " << studGender << endl;
            cout << "Class ID: " << studClassID << endl;
            cout << "Address: " << studAddress << endl;
            cout << "Phone: " << studPhone << endl;

            found = true;
            break;
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
    
    int roll;
    string studName, studGender, studClassID, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(inFile >> roll >> delimiter 
                  >> studName >> delimiter 
                  >> studAge >> delimiter 
                  >> studGender >> delimiter 
                  >> studClassID >> delimiter 
                  >> studAddress >> delimiter 
                  >> studPhone)
    {
        if(roll == rollToUpdate)
        {
            found = true;
            cout << "Enter new details for roll number " << roll << ":" << endl;
            
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, studName);
            
            cout << "Enter age: ";
            cin >> studAge;
            cin.ignore();
            
            cout << "Enter gender: ";
            getline(cin, studGender);
            cout << "Enter class ID: ";
            getline(cin, studClassID); 
            cout << "Enter address: ";
            getline(cin, studAddress);
            cout << "Enter phone number: ";
            getline(cin, studPhone);
            cout << "Student updated successfully!" << endl;
        }


        tempFile << roll << "|" 
                 << studName << "|" 
                 << studAge << "|" 
                 << studGender << "|" 
                 << studClassID << "|" 
                 << studAddress << "|" 
                 << studPhone << endl;
    }
    inFile.close();
    tempFile.close();
    remove("data/students.txt");
    rename("data/temp_students.txt", "data/students.txt");
    if(!found)
        cout << "Student not found!" << endl;
}