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
    int roll;
    string studName, studGender, studAddress, studPhone;
    int studAge;
    char delimiter;
    
    while(studentFile >> roll >> delimiter 
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
        int enrRoll;
        float enrTotal, enrPaid, enrRemaining;
        string enrDate;
        while(feesFile >> enrRoll >> delimiter >> enrTotal >> delimiter >> enrPaid >> delimiter >> enrRemaining >> delimiter >> enrDate)
        {
            if(enrRoll == rollNumber)
            {
                cout << "Fee record already exists for this student!" << endl;
                feesFile.close();
                return;
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
    
    int roll;
    float total, paid, remaining;
    string date;
    char delimiter;
    
    cout << "\n==== Fee Records ======" << endl;
    
    while(file >> roll >> delimiter >> total >> delimiter >> paid >> delimiter >> remaining >> delimiter >> date)
    {
        cout << "\nRoll Number: " << roll << endl;
        cout << "Total Fees: " << total << endl;
        cout << "Paid Fees: " << paid << endl;
        cout << "Remaining Fees: " << remaining << endl;
        cout << "Payment Date: " << date << endl;
        cout << "--------------------" << endl;
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
    
    int roll;
    float total, paid, remaining;
    string date;
    char delimiter;
    
    while(inFile >> roll >> delimiter >> total >> delimiter >> paid >> delimiter >> remaining >> delimiter >> date)
    {
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
    
    int roll;
    float total, paid, remaining;
    string date;
    char delimiter;
    
    while(inFile >> roll >> delimiter >> total >> delimiter >> paid >> delimiter >> remaining >> delimiter >> date)
    {
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
            
            remaining = total - paid;
            
            cout << "Fee record updated successfully!" << endl;
        }
        
        tempFile << roll << "|" << total << "|" << paid << "|" << remaining << "|" << date << endl;
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
    
    int roll;
    float total, paid, remaining;
    string date;
    char delimiter;
    
    while(inFile >> roll >> delimiter >> total >> delimiter >> paid >> delimiter >> remaining >> delimiter >> date)
    {
        if(roll == rollToDelete)
        {
            found = true;
            cout << "Fee record deleted successfully!" << endl;
        }
        else
        {
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
