#ifndef FEES_H
#define FEES_H


#include <string>
#include <iostream>

using namespace std;

class Fees {
    private:
        int rollNumber;
        float totalFees;
        float paidFees;
        float remainingFees;
        string paymentdate;
    public:

        Fees();

        //setters
        void setRollNumber(int rollNumber);
        void setTotalFees(float totalFees);
        void setPaidFees(float paidFees);
        void setRemainingFees(float remainingFees);
        void setPaymentdate(string paymentdate);
        //getters
        int getRollNumber() const;
        float getTotalFees() const;
        float getPaidFees() const;
        float getRemainingFees() const;
        string getPaymentdate() const;
        //member functions
        void enterfeerecord(int rollNumber);
        void displayfeerecord();
        void payfees(int rollNumber);
        void updatefeerecord(int rollNumber);
        void calculateRemainingFees();
        void savefeerecordToFile();
        void deletefeerecord(int rollNumber);
};


#endif
