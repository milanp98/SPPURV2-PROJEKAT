#pragma once

#include <memory.h>

#include "tbb/task.h"
#include "tbb/concurrent_queue.h"
#include <tbb/compat/thread>

#include "ResultsCollectorP.h"

using namespace tbb;
using namespace std;

// class for checking if a solution is unique, considering its rotations and symetries
class CUniqueSolutionP : public task
{
public:
    int n;                          // table size
    int *uniqueSolutionsNo;         // pointer to number of unique solutions
    concurrent_queue<int*>* queue;  // a queue with found solutions

    int* in90;      // in buffer rotated once
    int* in180;     // in buffer rotated twice
    int* in270;     // in buffer rotated thre times
    int* sim;       // symetre of in buffer
    int* sim90;     // symetre buffer rotated once
    int* sim180;    // symetre buffer rotated twice
    int* sim270;    // symetre buffer rotated thre times

    // constructor
    CUniqueSolutionP(int n, concurrent_queue<int*>* queue, int *uniqueSolutionsNo);

    // destructor
    ~CUniqueSolutionP(void);

    // make symetre
    // param:
    //      out - pointer to output buffer to write results (rotated in) to
    //      in - pointer to input buffer (values to be rotated)
    //      n - length of both in and out buffers
    void Symetre(int* out, int* in, int n);

    // rotate table
    // param:
    //      out - pointer to output buffer to write results (symetre of in) to
    //      in - pointer to input buffer
    //      n - length of both in and out buffers
    void Rotate(int* out, int* in, int n);

    // makes whole class of solutions, that holdes passed solution as well
    // checks if passed solution is lexicographically smallest
    // param:
    //      column - a buffer with found solution
    int Run(int* column);

    // task that takes found solution (pointer to column buffer) from queue and calls run
    // finishes, if taken pointer is NULL
    task* execute();
};
