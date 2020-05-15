/// -------------------------------------------------------------------
/// Ebeling, George Assignment 1
/// CIS 263 - Dr. Leidig
/// This program asks for input from a user regarding loan information
/// and then prints an amortization table to the console and to a
/// .txt file.
/// -------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Loan.h"
#include "AmortizationTable.h"

using namespace std;

Loan GatherData();

int main() {

    Loan newLoan = GatherData();
    Loan *pLoan = &newLoan;
    AmortizationTable::makeAmortizationTable(pLoan);
//    AmortizationTable::makeAmortizationTable("test_01 loan", 180000, .04, 360, 300);


    return 0;
}

Loan GatherData()
{
    string loanName;
    double principle;
    double rate;
    int numMonths;
    double extra;

    cout << "Please enter a name for you loan: " << endl;
    getline(std::cin,loanName);

    cout <<"Please enter the principle value of the loan : " << endl;
    cin >> principle;

    cout <<"\nPlease enter the interest rate of the loan (ex. 0.06): " << endl;
    cin >> rate;
    rate = rate / 12;

    cout <<"\nPlease enter the number of months on the loan: " << endl;
    cin >> numMonths;

    cout <<"\nPlease enter the amount that will be added to each payment (enter 0 if none): " << endl;
    cin >> extra;

    return Loan(loanName,principle, rate, numMonths, extra);
}
