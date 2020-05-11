//
// Created by George on 5/11/2020.
//
#include <iostream>
#include <fstream>
#include <string>
#include "Loan.h"
#include <iomanip>
#include "AmortizationTable.h"


/// Make an amortization table with the given Loan.
/// The table is printed in the console and to a file.
void AmortizationTable::makeAmortizationTable(Loan *&pLoan) {

    // Make a loan file
    ofstream loanFile;

    // Verify that the loan file is available.
    bool safeToWrite = checkFile(pLoan, loanFile);

    //Print amortization header
    PrintLoanHeader(pLoan, cout); //Print to console
    PrintLoanOutput(pLoan, loanFile); //Print to file

    //Calculate the values for each month and then display those values in a table.
    while(pLoan->RunningPrinciple > 0)
    {
        pLoan->CalculateNewMonth(); //Start a new month
        PrintLoanOutput(pLoan, cout); //Print to console

        if(safeToWrite) PrintLoanOutput(pLoan, loanFile); //Print to file if safe
    }

    CloseLoanFile(loanFile, safeToWrite); // Close file once complete.
}

void AmortizationTable::makeAmortizationTable(string name, double principle, double rate, int months, double extra) {
    Loan newLoan = Loan(name, principle, rate, months, extra);
    Loan *pLoan = &newLoan;

    makeAmortizationTable(pLoan);
}

void AmortizationTable::makeAmortizationTable() {
    Loan newLoan = GatherData();
    Loan *pLoan = &newLoan;
    makeAmortizationTable(pLoan);
}

Loan AmortizationTable::GatherData()
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

    cout <<"\nPlease enter the interest rate of the loan : " << endl;
    cin >> rate;
    rate = rate / 12;

    cout <<"\nPlease enter the number of months on the loan: " << endl;
    cin >> numMonths;

    cout <<"\nPlease enter the amount that will be added to each payment (enter 0 if none): " << endl;
    cin >> extra;

    return Loan(loanName,principle, rate, numMonths, extra);
}

/// Create the header for the amortization table in the given stream.
void AmortizationTable::PrintLoanHeader(Loan *&myLoan, ostream & output)
{
    output << "----------------------------------" << endl;
    output << myLoan->LoanName << " -";
    output << fixed << setprecision(2) << " P:" << myLoan->RunningPrinciple;
    output << " n:" << myLoan->n;
    output << fixed << setprecision(3) << " r:" << myLoan->Rate*12;
    output << fixed << setprecision(2) << " e:" << myLoan->Extra;
    output << endl;
    output << "----------------------------------" << endl;
    output << "month\tmonthlyPayment\tprincipleRemaining\tprinciplePaid\tinterestPaid\ttotalPaid\ttotalPrinciplePaid\ttotalInterestPaid" << endl;
}

/// Display a single row of the amortization table in the given stream.
void AmortizationTable::PrintLoanOutput(Loan * &myLoan, ostream & output)
{
    output << fixed << setprecision(2);
    printLoanElement(myLoan->monthsPassed, 8, output);
    printLoanElement(myLoan->Monthlypayment, 16, output);
    printLoanElement(myLoan->RunningPrinciple, 20, output);
    printLoanElement(myLoan->monthPrincePaid,16, output);
    printLoanElement(myLoan->monthInterestPaid,16, output);
    printLoanElement(myLoan->totalPaid, 12, output);
    printLoanElement(myLoan->totalPrinciplePaid, 20, output);
    printLoanElement(myLoan->totalInterestPaid, 10, output);
    output << endl;
}

/// Close the loan file, or notify the user that it was not written to.
void AmortizationTable::CloseLoanFile(ofstream &loanFile, bool safeToWrite) {
    if(!safeToWrite) {
        cout << "Loan file could not be written to";
    }
    loanFile.close();
}

/// Verify that it is safe to write to the loanFile.
bool AmortizationTable::checkFile(Loan *const &pLoan, ofstream &loanFile) {
    if(!loanFile.is_open()) {
        string fileName = pLoan->LoanName + ".txt";
        loanFile.open(fileName);
        return true;
    }
    return false;
}

/// Push t into the given output stream.
template<typename T>
void AmortizationTable::printLoanElement(T t, const int & width, ostream &output) {
    output << left << setw(width) << t;
}

