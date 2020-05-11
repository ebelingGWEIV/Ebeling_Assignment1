#include <iostream>
#include <fstream>
#include <string>
#include "Loan.h"
#include <iomanip>
#include "AmortizationTable.h"

void AmortizationTable::makeAmortizationTable(Loan *&pLoan) {

    // Make a loan file
    ofstream loanFile;
    // Verify that the loan file is available.
    bool safeToWrite = checkLoanFile(pLoan, loanFile);

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

void AmortizationTable::PrintLoanHeader(Loan *&myLoan, ostream & output)
{
    output << fixed << setprecision(2); // Set the float precision.

    output << "---------------------------------------------" << endl;
    output << myLoan->LoanName << " -";
    output << " P:" << myLoan->RunningPrinciple;
    output << " n:" << myLoan->totalMonths;
    output << " r:" << myLoan->Rate*12*100 << "%"; //convert the rate into a percent
    output  << " e:" << myLoan->Extra;
    output << endl;
    output << "---------------------------------------------" << endl;
    output << "month\tmonthlyPayment\tprincipleRemaining\tprinciplePaid\tinterestPaid\ttotalPaid\ttotalPrinciplePaid\ttotalInterestPaid" << endl;
}

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

void AmortizationTable::CloseLoanFile(ofstream &loanFile, bool safeToWrite) {
    if(!safeToWrite) {
        cout << "Loan file could not be written to";
    }
    loanFile.close();
}

bool AmortizationTable::checkLoanFile(Loan *const &pLoan, ofstream &loanFile) {
    if(!loanFile.is_open()) {
        string fileName = pLoan->LoanName + ".txt";
        loanFile.open(fileName);
        return true;
    }
    return false;
}


template<typename T>
void AmortizationTable::printLoanElement(T t, const int & width, ostream &output) {
    output << left << setw(width) << t;
}

