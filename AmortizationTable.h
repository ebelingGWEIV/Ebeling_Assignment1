//
// Created by George on 5/11/2020.
//

#ifndef EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
#define EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H

using namespace std;

class AmortizationTable {

private:
    static void PrintLoanHeader(Loan *&, ostream &);
    static void  PrintLoanOutput(Loan *&, ostream &);
    template<typename T> static void printLoanElement(T , const int &, ostream &);
    static bool checkFile(Loan *const &pLoan, ofstream &loanFile);
    static void CloseLoanFile(ofstream &loanFile, bool safeToWrite);
    static Loan GatherData();
public:
    static void makeAmortizationTable(Loan *&pLoan);
    static void makeAmortizationTable(string, double, double, int, double);
    static void makeAmortizationTable();
};


#endif //EBELING_ASSIGNMENT1_AMORTIZATIONTABLE_H
