//
// Created by George on 5/8/2020.
//

#ifndef EBELINGASSIGNMENT1_LOAN_H
#define EBELINGASSIGNMENT1_LOAN_H

#include <string>

using namespace std;

class Loan {

private:
    /// Adjust the last monthly payment to prevent overpaying.
    void LastMonth();

    /// Increase the current month.
    void IncrementMonths() {monthsPassed++;}

public:
    string LoanName = "";
    double Monthlypayment = 0;
    double RunningPrinciple = 0;
    double Rate = 0;
    int totalMonths = 0; // Number of months on the loan
    int monthsPassed = -1; //Running total for months passed

    double Extra = 0;
    double totalPrinciplePaid = 0;
    double totalInterestPaid = 0;
    double totalPaid = 0;
    double monthPrincePaid = 0;
    double monthInterestPaid = 0;

    /// Create a new loan.
    Loan(string, double, double, int, double);

    /// Calculate the minimum monthly payment for a loan
    static double calculateMonthlyPayment(double principle, double rate, int months, double extra) ;

    /// Calculate the money going to towards interest this month.
    double InterestPaidThisMonth() const ;

    /// Calculate the money going towards the principle this month.
    double PrinciplePaidThisMonth() ;

    /// Calculate the values for a new month.
    void CalculateNewMonth();
};

#endif //EBELINGASSIGNMENT1_LOAN_H
