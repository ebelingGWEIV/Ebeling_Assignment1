#include "Loan.h"
#include <iostream>


Loan::Loan(string name, double principle, double rate, int months, double extra) {
    this->LoanName = name;
    this->RunningPrinciple = principle;
    this->Rate = rate / 12;
    this->Extra = extra;
    this->Monthlypayment = calculateMonthlyPayment(RunningPrinciple, Rate, months, Extra);
}

double Loan::calculateMonthlyPayment(double principle, double rate, int months, double extra)
{
    double numer = rate * principle * pow(1+rate,months);
    double denom = -1 + pow((1+rate),months);
    double monthly = numer/denom;

    return monthly+extra;
}

void Loan::CalculateNewMonth() {
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

void Loan::LastMonth(){
    Monthlypayment = RunningPrinciple + monthInterestPaid;
}

double Loan::InterestPaidThisMonth() const {
    return RunningPrinciple * Rate;
}

double Loan::PrinciplePaidThisMonth() {
    if(Monthlypayment <= RunningPrinciple)
        return Monthlypayment - RunningPrinciple * Rate + Extra;
    else {
        LastMonth();
        return RunningPrinciple;
    }
}