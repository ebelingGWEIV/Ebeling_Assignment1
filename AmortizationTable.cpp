/// -------------------------------------------------------------------
/// Ebeling, George Assignment 1
/// CIS 263 - Dr. Leidig
/// Implements AmortizationTable.h to print an Amortization table in
/// the console and a .txt file.
/// -------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "Loan.h"
#include <iomanip>
#include <utility>
#include <filesystem>
#include "AmortizationTable.h"

/// Creates an amortization table and prints to the console and creates an output .txt file with the same name as the loan.
/// \param pLoan Loan to create a table for. Only remaining months will be shown.
void AmortizationTable::makeAmortizationTable(Loan *&pLoan) {

    // Make a loan file
    ofstream loanFile;

    bool fileCreated = OpenLoanFile(pLoan, loanFile);

    //Print amortization header
    PrintLoanHeader(pLoan, cout); //Print to console
    PrintLoanHeader(pLoan, loanFile); //Print to file

    //Calculate the values for each month and then display those values in a table.
    while(pLoan->GetRunningPrinciple() > 0)
    {
        pLoan->CalculateNewMonth(); //Start a new month
        PrintLoanOutput(pLoan, cout); //Print to console

        PrintLoanOutput(pLoan, loanFile); //Print to file
    }

    CloseLoanFile(loanFile, fileCreated); // Close file stream once complete.
}

/// Make an amortization table given the loan information.
/// \param name A name for the loan
/// \param principle Amount owed on the loan
/// \param rate Annual interest rate of the loan
/// \param months Number of months remaining on the loan
/// \param extra Additional amount to pay during each monthly payment
void AmortizationTable::makeAmortizationTable(string name, double principle, double rate, int months, double extra) {
    Loan newLoan = Loan(std::move(name), principle, rate, months, extra);
    Loan *pLoan = &newLoan;

    makeAmortizationTable(pLoan);
}

/// Create the header for the amortization table in the given stream.
/// \param myLoan Loan to print
/// \param output Stream to print to
void AmortizationTable::PrintLoanHeader(Loan *&myLoan, ostream & output)
{
    output << fixed << setprecision(2); // Set the float precision.

    output << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
    output << myLoan->GetLoanName() << " -";
    output << " P:" << myLoan->GetRunningPrinciple();
    output << " n:" << myLoan->GetTotalMonths();
    output << " r:" << myLoan->GetRate()*12*100 << "%"; //convert the rate into a percent
    output  << " e:" << myLoan->GetExtra();
    output << endl;
    output << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
    output << "month\tmonthlyPayment\tprincipleRemaining\tprinciplePaid\tinterestPaid\ttotalPaid\ttotalPrinciplePaid\ttotalInterestPaid" << endl;
}

/// Display a single row of the amortization table in the given stream.
/// \param myLoan Loan to print
/// \param output Stream to print to
void AmortizationTable::PrintLoanOutput(Loan * &myLoan, ostream & output)
{
    output << fixed << setprecision(2); // Set the float precision

    printLoanElement(myLoan->GetMonthsPassed(), 8, output);
    printLoanElement(myLoan->GetMonthlyPayment(), 16, output);
    printLoanElement(myLoan->GetRunningPrinciple(), 20, output);
    printLoanElement(myLoan->GetMonthPrinciplePaid(), 16, output);
    printLoanElement(myLoan->GetMonthInterestPaid(),16, output);
    printLoanElement(myLoan->GetTotalPaid(), 12, output);
    printLoanElement(myLoan->GetTotalPrinciplePaid(), 20, output);
    printLoanElement(myLoan->GetTotalInterestPaid(), 10, output);
    output << endl;
}

/// Close the loan file.
/// \param loanFile The ofstream to close
/// \param fileCreated A flag for the existence of the loan file.
void AmortizationTable::CloseLoanFile(ofstream &loanFile, bool fileCreated) {
    if(!fileCreated) cout << endl << "Output file was not created or written to" << endl;
    loanFile.close();
}

/// Creates a new Loan file. Will overwrite an existing .txt file of the same loan name.
/// \param pLoan The loan object that will be using the file.
/// \param loanFile File stream for the file to be written to.
/// \return True if the loan file exists
bool AmortizationTable::OpenLoanFile(Loan *const &pLoan, ofstream &loanFile) {
    string fileName = pLoan->GetLoanName() + ".txt";
    loanFile.open(fileName);

    return filesystem::exists(pLoan->GetLoanName() + ".txt");
}

/// Push t into the given output stream.
/// \param t Information to push into the stream.
/// \param width Amount of space to be allotted.
/// \param output The stream to push information to.
template<typename T>
void AmortizationTable::printLoanElement(T t, const int & width, ostream &output) {
    output << left << setw(width) << t;
}

