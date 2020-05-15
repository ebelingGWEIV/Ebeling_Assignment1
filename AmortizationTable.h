/// -------------------------------------------------------
/// Ebeling, George Assignment 1
/// CIS 263 - Dr. Leidig
/// This class builds an amortization table by accepting either a Loan
/// object or the information to construct a Loan object.
/// The amortization table is printed to the console and to an output
/// file with the same name as the loan.
/// -------------------------------------------------------------------


#ifndef EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
#define EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H

using namespace std;

class AmortizationTable {

private:

    static void PrintLoanHeader(Loan *&, ostream &);


    static void  PrintLoanOutput(Loan *&, ostream &);


    static void CloseLoanFile(ofstream & );


    static void OpenLoanFile(Loan *const &pLoan, ofstream &loanFile);


    template<typename T> static void printLoanElement(T t, const int & , ostream &);

public:

    static void makeAmortizationTable(Loan *& );

    static void makeAmortizationTable(string , double , double , int , double );

};


#endif //EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
