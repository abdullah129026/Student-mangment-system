#include "Fees.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Constructor
Fees::Fees() {
    rollNumber = 0;
    totalFees = 0.0;
    paidFees = 0.0;
    remainingFees = 0.0;
    paymentdate = "";
}

//Setters
void Fees::setRollNumber(int rollNumber) {
    this->rollNumber = rollNumber;
}

void Fees::setTotalFees(float totalFees) {
    this->totalFees = totalFees;
}

void Fees::setPaidFees(float paidFees) {
    this->paidFees = paidFees;
}

void Fees::setRemainingFees(float remainingFees) {
    this->remainingFees = remainingFees;
}

void Fees::setPaymentdate(string paymentdate) {
    this->paymentdate = paymentdate;
}

//Getters
int Fees::getRollNumber() const {
    return rollNumber;
}

float Fees::getTotalFees() const {
    return totalFees;
}

float Fees::getPaidFees() const {
    return paidFees;
}

float Fees::getRemainingFees() const {
    return remainingFees;
}

string Fees::getPaymentdate() const {
    return paymentdate;
}

//member functions
void Fees::enterfeerecord(int rollNumber)
{
    //verify student exists
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
    studentFile.close();
    if(!studentFound)
    {
        cout << "Student with roll number " << rollNumber << " not found!" << endl;
        return;
    }
    
    
    //fee record already exists
    ifstream feesFile("data/fees.txt");
    if(feesFile.is_open())
    {
        while(getline(feesFile, line))
        {
            if(line.empty()) continue;
            
            size_t pipePos = line.find('|');
            if(pipePos != string::npos) {
                int enrRoll = stoi(line.substr(0, pipePos));
                if(enrRoll == rollNumber)
                {
                    cout << "Fee record already exists for this student!" << endl;
                    feesFile.close();
                    return;
                }
            }
        }
        feesFile.close();
    }
    
    // Now enter fee record
    cout << "Enter total fees: ";
    cin >> totalFees;
    cout << "Enter paid fees: ";
    cin >> paidFees;
    cout << "Enter payment date: ";
    cin.ignore();
    getline(cin, paymentdate);
    
    setRollNumber(rollNumber);
    calculateRemainingFees();
    savefeerecordToFile();
}

void Fees::displayfeerecord()
{
    ifstream file("data/fees.txt");
    if(!file.is_open())
    {
        cout << "Error opening fees file!" << endl;
        return;
    }
    
    string line;
    cout << "\n==== Fee Records ======" << endl;
    
    while(getline(file, line))
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
        
        if(fields.size() >= 5) {
            cout << "\nRoll Number: " << fields[0] << endl;
            cout << "Total Fees: " << fields[1] << endl;
            cout << "Paid Fees: " << fields[2] << endl;
            cout << "Remaining Fees: " << fields[3] << endl;
            cout << "Payment Date: " << fields[4] << endl;
            cout << "--------------------" << endl;
        }
    }
    
    file.close();
}

void Fees::payfees(int rollNumber)
{
    ifstream inFile("data/fees.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening fees file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_fees.txt");
    bool found = false;
    string line;
    
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
        
        if(fields.size() >= 5) {
            int roll = stoi(fields[0]);
            float total = stof(fields[1]);
            float paid = stof(fields[2]);
            float remaining = stof(fields[3]);
            string date = fields[4];
            
            if(roll == rollNumber)
            {
                found = true;
                cout << "Enter amount to pay: ";
                float paymentAmount;
                cin >> paymentAmount;
                
                paid += paymentAmount;
                remaining = total - paid;
                
                if(remaining < 0)
                {
                    cout << "Warning: Payment exceeds remaining fees!" << endl;
                    remaining = 0;
                }
                
                cout << "Enter new payment date: ";
                cin.ignore();
                getline(cin, date);
                
                cout << "Payment recorded successfully!" << endl;
                cout << "Remaining fees: " << remaining << endl;
            }
            
            tempFile << roll << "|" << total << "|" << paid << "|" << remaining << "|" << date << endl;
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/fees.txt");
    rename("data/temp_fees.txt", "data/fees.txt");
    
    if(!found)
        cout << "Fee record not found!" << endl;
}

void Fees::updatefeerecord(int rollNumber)
{
    ifstream inFile("data/fees.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening fees file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_fees.txt");
    bool found = false;
    string line;
    
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
        
        if(fields.size() >= 5) {
            int roll = stoi(fields[0]);
            float total = stof(fields[1]);
            float paid = stof(fields[2]);
            string date = fields[4];
            
            if(roll == rollNumber)
            {
                found = true;
                cout << "Enter updated total fees: ";
                cin >> total;
                
                cout << "Enter updated paid fees: ";
                cin >> paid;
                
                cout << "Enter payment date: ";
                cin.ignore();
                getline(cin, date);
                
                float remaining = total - paid;
                
                tempFile << roll << "|" << total << "|" << paid << "|" << remaining << "|" << date << endl;
                
                cout << "Fee record updated successfully!" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/fees.txt");
    rename("data/temp_fees.txt", "data/fees.txt");
    
    if(!found)
        cout << "Fee record not found!" << endl;
}

void Fees::calculateRemainingFees() {
    remainingFees = totalFees - paidFees;
}

void Fees::savefeerecordToFile()
{
    ofstream outFile("data/fees.txt", ios::app);
    if(outFile.is_open())
    {
        outFile << rollNumber << "|" 
                << totalFees << "|" 
                << paidFees << "|" 
                << remainingFees << "|" 
                << paymentdate << endl;
        outFile.close();
        cout << "Fee record saved successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
    }
}

void Fees::deletefeerecord(int rollToDelete)
{
    ifstream inFile("data/fees.txt");
    if(!inFile.is_open())
    {
        cout << "Error opening fees file!" << endl;
        return;
    }
    
    ofstream tempFile("data/temp_fees.txt");
    bool found = false;
    string line;
    
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
        
        if(fields.size() >= 5) {
            int roll = stoi(fields[0]);
            
            if(roll == rollToDelete)
            {
                found = true;
                cout << "Fee record deleted successfully!" << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("data/fees.txt");
    rename("data/temp_fees.txt", "data/fees.txt");
    
    if(!found)
        cout << "Fee record not found!" << endl;
}
