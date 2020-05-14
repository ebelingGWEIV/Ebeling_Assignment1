//
// Created by George on 5/8/2020.
//

#ifndef EBELINGASSIGNMENT1_LOAN_H
#define EBELINGASSIGNMENT1_LOAN_H

#include <string>
#include <utility>

using namespace std;

class Loan {

private:
    /// Adjust the last monthly payment to prevent overpaying.
    void LastMonth(){
        Monthlypayment = RunningPrinciple + monthInterestPaid;
    }

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
    Loan(string name, double principle, double rate, int months, double extra) {
        this->LoanName = std::move(name);
        this->RunningPrinciple = principle;
        this->Rate = rate / 12;
        this->Extra = extra;
        this->totalMonths = months;
        this->Monthlypayment = calculateMonthlyPayment(RunningPrinciple, Rate, months, Extra);
    }

    /// Calculate the minimum monthly payment for a loan
    static double calculateMonthlyPayment(double principle, double rate, int months, double extra)
    {
        double numer = rate * principle * pow(1+rate,months);
        double denom = -1 + pow((1+rate),months);
        double monthly = numer/denom;

        return monthly+extra;
    }

    /// Calculate the money going to towards interest this month.
    double InterestPaidThisMonth() const {
        return RunningPrinciple * Rate;
    }

    /// Calculate the money going towards the principle this month.
    double PrinciplePaidThisMonth() {
        if(Monthlypayment <= RunningPrinciple)
            return (Monthlypayment - Extra) - RunningPrinciple * Rate + Extra; //extra is accounted for in monthly payment, but needed to be removed for this calculation
        else {
            LastMonth();
            return RunningPrinciple;
        }
    }

    /// Calculate the values for a new month.
    void CalculateNewMonth() {
        //Calculate the payments needed for this month
        monthInterestPaid = InterestPaidThisMonth();
        monthPrincePaid = PrinciplePaidThisMonth();

        //Calculate the sum totals
        totalPrinciplePaid += monthPrincePaid;
        totalInterestPaid += monthInterestPaid;
        RunningPrinciple -= monthPrincePaid;
        totalPaid = totalPrinciplePaid + totalInterestPaid;

        //Increase to the next month
        IncrementMonths();
    }
};

#endif //EBELINGASSIGNMENT1_LOAN_H
