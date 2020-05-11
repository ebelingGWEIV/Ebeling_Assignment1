#ifndef EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
#define EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H

using namespace std;

class AmortizationTable {

private:
    /// Create the header for the amortization table in the given stream.
    static void PrintLoanHeader(Loan *&, ostream &);

    /// Display a single row of the amortization table in the given stream.
    static void  PrintLoanOutput(Loan *&, ostream &);

    /// Close the loan file, or notify the user that it was not written to.
    static void CloseLoanFile(ofstream &loanFile, bool safeToWrite);

    /// Verify that it is safe to write to the loanFile.
    static bool checkLoanFile(Loan *const &pLoan, ofstream &loanFile);

    /// Push t into the given output stream.
    /// \param t Information to push into the stream.
    /// \param width Amount of space to be allotted.
    /// \param output The stream to push information to.
    template<typename T> static void printLoanElement(T t, const int & width, ostream &output);
public:

    /// Make an amortization table with the given Loan.
    /// The table is printed in the console and to a file.
    static void makeAmortizationTable(Loan *&);

    /// Make an amortization table with the given information.
    static void makeAmortizationTable(string, double, double, int, double);
};


#endif //EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
