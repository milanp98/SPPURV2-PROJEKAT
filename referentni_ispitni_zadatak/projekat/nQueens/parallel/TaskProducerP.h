#pragma once

#include <iostream>
#include <fstream>

#include "tbb/task.h"

#include "nQueensP.h"

using namespace tbb;
using namespace std;

// class for reading input file and producing NQueens tasks
class CTaskProducerP : public task
{
    char* inFileName;                                       // input file name
    char* outFileName;                                      // output file name
    ifstream inFile;                                        // input file
    concurrent_queue<ResultsCollectorParam*> result_queue;  // queue with results (filled by NQueensP, read by CResultsCollector
public:

    // constructor
    // param:
    //      inFileName - input file name
    //      outFileName - output file name
    CTaskProducerP(char* nFileName, char* outFileName);

    // destructor
    ~CTaskProducerP(void);

    // task that reads input file
    // creates CResultsCollectorP task
    // creates CNQueensP task for each read parameter and waits for them to finish
    // send NULL to CResultsCollectorP task to finish (through result_queue)
    // waits for CResultsCollectorP task to finish
	task* execute();
};
