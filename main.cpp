#include <iostream>
#include <fstream>
#include <string>
#include "Loan.h"
#include <iomanip>

using namespace std;

Loan GatherData();

void PrintLoanHeader(Loan *&, ostream &);
void  PrintLoanOutput(Loan *&, ostream &);
void makeAmortizationTable(Loan *&pLoan);
template<typename T> void printLoanElement(T , const int &, ostream &);
bool checkFile(Loan *const &pLoan, ofstream &loanFile);
void CloseLoanFile(ofstream &loanFile, bool safeToWrite);

int main() {

//    Loan newLoan = GatherData();
    Loan newLoan = Loan("new loan", 15007, .06, 36, 100);
    Loan *pLoan = &newLoan;

    makeAmortizationTable(pLoan);

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

    cout <<"\nPlease enter the interest rate of the loan : " << endl;
    cin >> rate;
    rate = rate / 12;

    cout <<"\nPlease enter the number of months on the loan: " << endl;
    cin >> numMonths;

    cout <<"\nPlease enter the amount that will be added to each payment (enter 0 if none): " << endl;
    cin >> extra;

    return Loan(loanName,principle, rate, numMonths, extra);
}

/// Make an amortization table with the given Loan.
/// The table is printed in the console and to a file.
void makeAmortizationTable(Loan *&pLoan) {

    //Make a loan file
    ofstream loanFile;
    bool safeToWrite = checkFile(pLoan, loanFile);

    //Print amortization header
    PrintLoanHeader(pLoan, cout); //Print to console
    PrintLoanOutput(pLoan, loanFile); //Print to file

    //Calculate the values for each month and then display those values in a table.
    while(pLoan->P > 0)
    {
        pLoan->NewMonth(); //Start a new month
        PrintLoanOutput(pLoan, cout); //Print to console

        if(safeToWrite) PrintLoanOutput(pLoan, loanFile); //Print to file if safe

        pLoan->IncrementMonths();
    }

    CloseLoanFile(loanFile, safeToWrite);
}

/// Create the header for the amortization table in the given stream.
void PrintLoanHeader(Loan *&myLoan, ostream & output)
{
    output << "----------------------------------" << endl;
    output << myLoan->LoanName << " P:" << myLoan->P << " n:" << myLoan->n << " r" << myLoan->r << " e:" << myLoan->e << endl;
    output << "----------------------------------" << endl;
    output << "month\tmonthlyPayment\tprincipleRemaining\tprinciplePaid\tinterestPaid\ttotalPaid\ttotalPrinciplePaid\ttotalInterestPaid" << endl;
}

/// Display a single row of the amortization table in the given stream.
void PrintLoanOutput(Loan * &myLoan, ostream & output)
{
    output << fixed << setprecision(2);
    printLoanElement(myLoan->monthsRemaining, 8, output);
    printLoanElement(myLoan->M,16, output);
    printLoanElement(myLoan->P,20, output);
    printLoanElement(myLoan->monthPrincePaid,16, output);
    printLoanElement(myLoan->monthInterestPaid,16, output);
    printLoanElement(myLoan->totalPaid, 12, output);
    printLoanElement(myLoan->totalPrinciplePaid, 20, output);
    printLoanElement(myLoan->totalInterestPaid, 10, output);
    output << endl;
}

/// Push t into the given output stream.
template<typename T> void printLoanElement(T t, const int &width, ostream & output)
{
    output << left << setw(width) << t;
}

/// Close the loan file, or notify the user that it was not written to.
void CloseLoanFile(ofstream &loanFile, bool safeToWrite) {
    if(!safeToWrite) {
        cout << "Loan file could not be written to";
    }
    loanFile.close();
}

/// Verify that it is safe to write to the loanFile.
bool checkFile(Loan *const &pLoan, ofstream &loanFile) {
    if(!loanFile.is_open()) {
        string fileName = pLoan->LoanName + ".txt";
        loanFile.open(fileName);
        return true;
    }
    return false;
}
