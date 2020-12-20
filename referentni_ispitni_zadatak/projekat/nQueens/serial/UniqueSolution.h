#pragma once

#include <memory.h>

#include "Task.h"

// parameters passed to Run method of CUniqueSolution
struct UniqueSolutionParam
{
    int n;                  // table (column buffer) size
    int *column;            // buffer with found solution
    int *uniqueSolutionsNo; // pointer to nubmer of solutions
};

// class for checking if a solution is unique, considering its rotations and symetries
class CUniqueSolution : public CTask
{
public:

    // constructor
    CUniqueSolution(void);

    // destructor
    ~CUniqueSolution(void);

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
    //      param - pointer to UniqueSolutionParam structure with found solution
    virtual int Run(void *param = NULL);
};
