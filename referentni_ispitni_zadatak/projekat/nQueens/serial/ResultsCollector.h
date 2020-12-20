#pragma once

#include <iostream>
#include <stdio.h>
#include <fstream>

#include "Task.h"

using namespace std;

// parameters passed to Run method of CResultsCollector
struct ResultsCollectorParam
{
    int n;                  // table (column buffer) size
    int totalSolutionsNo;   // total number of solutions
    int uniqueSolutionsNo;  // nubmer of unique solutions
};


// class for collecting results from NQueens
class CResultsCollector : public CTask
{
private:
    char* outFileName;  // output file name to write results to
    ofstream outFile;   // output file
public:

    // constructor
    // param:
    //      outFileName - output file name
    CResultsCollector(char* outFileName);

    // destructor
    ~CResultsCollector(void);

    // writes results passed through param to output file
    // param:
    //      param - pointer to ResultsCollectorParam structure with results
    virtual int Run(void* param = NULL);
};
