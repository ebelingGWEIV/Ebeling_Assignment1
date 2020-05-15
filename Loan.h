/// -------------------------------------------------------------------
/// Ebeling, George Assignment 1
/// CIS 263 - Dr. Leidig
/// Stores and claculates Loan information.
/// Calling CalcualteNewMonth will refresh calculated values for a
/// new month.
/// -------------------------------------------------------------------

#ifndef EBELINGASSIGNMENT1_LOAN_H
#define EBELINGASSIGNMENT1_LOAN_H

#include <string>
#include <utility>

using namespace std;

class Loan {

private:
    string LoanName = "";
    double RunningPrinciple = 0;
    double Rate = 0;
    int totalMonths = 0; // Number of months on the loan

    int monthsPassed = -1; //Running total for months passed
    double MonthlyPayment = 0; //Amount to pay each month
    double Extra = 0; // Amount extra to pay each month
    double totalPrinciplePaid = 0;
    double totalInterestPaid = 0;
    double totalPaid = 0;
    //These two monthly values are stored to reduce the number of calculations made per month
    double monthPrincePaid = 0;
    double monthInterestPaid = 0;

    /// Adjust the last monthly payment to prevent overpaying.
    void LastMonth(){
        MonthlyPayment = RunningPrinciple + monthInterestPaid;
    }

    /// Increase the current month by one.
    void IncrementMonths() {monthsPassed++;}

public:


    string GetLoanName() { return LoanName;}
    [[nodiscard]] double GetRunningPrinciple() const { return RunningPrinciple; }
    [[nodiscard]] int GetTotalMonths() const { return totalMonths; }

    /// \return The annual interest rate of the loan.
    [[nodiscard]] double GetRate() const { return Rate*12; }
    [[nodiscard]] double GetExtra() const { return Extra; }

    [[nodiscard]] double GetMonthsPassed() const { return monthsPassed; }
    [[nodiscard]] double GetMonthlyPayment() const { return MonthlyPayment; }
    [[nodiscard]] double GetMonthPrinciplePaid() const { return monthPrincePaid; }
    [[nodiscard]] double GetMonthInterestPaid() const { return monthInterestPaid; }
    [[nodiscard]] double GetTotalPaid() const { return totalPaid; }
    [[nodiscard]] double GetTotalPrinciplePaid() const {return totalPrinciplePaid; }
    [[nodiscard]] double GetTotalInterestPaid() const { return totalInterestPaid; }


    /// Create a new loan.
    /// \param name A label for the loan
    /// \param principle Amount owed on the loan
    /// \param rate Annual interest rate of the loan
    /// \param months Number of months on the loan
    /// \param extra Additonal funds to pay beyond the required minimum payment
    Loan(string name, double principle, double rate, int months, double extra) {
        this->LoanName = std::move(name);
        this->RunningPrinciple = principle;
        this->Rate = rate / 12;
        this->Extra = extra;
        this->totalMonths = months;
        this->MonthlyPayment = calculateMonthlyPayment(RunningPrinciple, Rate, months, Extra);
    }

    /// Calculate the minimum monthly payment for a loan.
    /// \param principle Amount owed on the loan
    /// \param rate Monthly interest rate of the loan
    /// \param months Number of months on the loan
    /// \param extra Additional funds to pay beyond the required minimum payment
    /// \return Minimum monthly payment
    static double calculateMonthlyPayment(double principle, double rate, int months, double extra)
    {
        double numer = rate * principle * pow(1+rate,months);
        double denom = -1 + pow((1+rate),months);
        double monthly = numer/denom;

        return monthly+extra;
    }

    /// Calculate the money going to towards interest this month.
    /// \return The number of dollars that went towards paying off interest this month.
    [[nodiscard]] double InterestPaidThisMonth() const {
        return RunningPrinciple * Rate;
    }

    /// Calculate the money going towards the principle this month.
    /// \return The number of dollars that went towards paying off the principle this month.
    double PrinciplePaidThisMonth() {
        //If the monthly payment is less than the remaining principle, pay the monthly payment
        if(MonthlyPayment <= RunningPrinciple)
            //extra is accounted for in monthly payment, but needed to be removed for this calculation
            return (MonthlyPayment - Extra) - RunningPrinciple * Rate + Extra; //Likely the source of calculation errors
        else {
            LastMonth();
            return RunningPrinciple;
        }
    }

    /// Calculate the values for a new month. Updates running totals: totalPrinciplePaid, totalInterestPaid, RunningPrinciple, and totalPaid.
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
