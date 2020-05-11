#include "Loan.h"
#include <iostream>


using namespace std;

Loan::Loan(string name, double principle, double rate, int months, double extra) {
    LoanName = name;
    P = principle;
    r = rate/12;
    e = extra;
    M = calculateMonthlyPayment(P, r, months, e);
}

double Loan::calculateMonthlyPayment(double principle, double rate, int months, double extra) const
{
    double numer = rate * principle * pow(1+rate,months);
    double denom = -1 + pow((1+rate),months);
    double monthly = numer/denom;

    return monthly+extra;
}

void Loan::NewMonth() {
    //Calculate the payments needed for this month
    monthInterestPaid = InterestPaidThisMonth();
    monthPrincePaid = PrinciplePaidThisMonth();

    //Calculate the sum totals
    totalPrinciplePaid += monthPrincePaid;
    totalInterestPaid += monthInterestPaid;
    P -= monthPrincePaid;
    totalPaid = totalPrinciplePaid + totalInterestPaid;
}

void Loan::LastMonth(){
    M = P + monthInterestPaid;
}

double Loan::InterestPaidThisMonth() const {
    return P*r;
}

double Loan::PrinciplePaidThisMonth() {
    if(M <= P)
        return M - P * r + e;
    else {
        LastMonth();
        return P;
    }
}