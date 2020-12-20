#pragma once

#include <iostream>
#include <stdio.h>
#include <fstream>

#include "tbb/task.h"
#include "tbb/concurrent_queue.h"
#include <tbb/compat/thread>

using namespace std;
using namespace tbb;

// parameters passed to Run method of CResultsCollector
struct ResultsCollectorParam
{
    int n;                  // table (column buffer) size
    int totalSolutionsNo;   // total number of solutions
    int uniqueSolutionsNo;  // nubmer of unique solutions
};

class CResultsCollectorP : public task
{
private:
    concurrent_queue<ResultsCollectorParam*>* queue;    // queue with new results that should be written to output file
    char* outFileName;                                  // output file name
    ofstream outFile;                                   // output file
public:

    // constructor
    // param:
    //      outFileName - output file name
    //      queue - pointer to queue with new results
    CResultsCollectorP(char* outFileName, concurrent_queue<ResultsCollectorParam*>* queue);

    // destructor
    ~CResultsCollectorP(void);

    // task that takes result (pointer to ResultsCollectorParam) and writes result to output file
    // finishes, if taken pointer is NULL
    task* execute();
};
