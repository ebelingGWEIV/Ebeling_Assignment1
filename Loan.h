//
// Created by George on 5/8/2020.
//

#ifndef EBELINGASSIGNMENT1_LOAN_H
#define EBELINGASSIGNMENT1_LOAN_H

#include <string>

using namespace std;

class Loan {

private:
    void LastMonth();
public:

    string LoanName = "";
    double M = 0;
    double P = 0;
    double r = 0;
    int n = 0;
    int monthsRemaining = 0;
    double e = 0;

    double totalPrinciplePaid = 0;
    double totalInterestPaid = 0;
    double totalPaid = 0;
    double monthPrincePaid = 0;
    double monthInterestPaid = 0;


    Loan(string, double, double, int, double);

    /// Calculate the minimum monthly payment for a loan
    double calculateMonthlyPayment(double principle, double rate, int months, double extra) const;

    double InterestPaidThisMonth() const ;

    double PrinciplePaidThisMonth() ;

    void IncrementMonths() {monthsRemaining++;}

    void NewMonth();
};


#endif //EBELINGASSIGNMENT1_LOAN_H
