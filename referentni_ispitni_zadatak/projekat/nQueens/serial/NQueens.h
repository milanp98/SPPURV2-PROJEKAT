#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "Task.h"
#include "UniqueSolution.h"
#include "ResultsCollector.h"

using namespace std;

// class for solving n-queens problem
class CNQueens : public CTask
{
public:
	int n;                          // n parameter from n-queens problem (size of table nxn, number of queens)
	int *column;                    // column array (each index corresponds to row, while writen value is column)
	int uniqueSolutionsNo;          // number of unique solutions
	int totalSolutionsNo;           // number of all solutions
    CTask* updateUniqueSolutionsNo; // task to check if current solution is unique, and update uniqueSolutionsNO accordingly
    CTask* passResult;              // task to pass result to

public:
    // constructor
    // params:
    //      updateUniqueSolutionsNo - task to check if current solution is unique
    //      passResult - task to pass calculated result
    CNQueens(CTask* updateUniqueSolutionsNo, CTask* passResult);

    // destructor
    ~CNQueens(void);

    // init and start algorithm
    void Solve();

    // print results
    void Print();

    // check if the queen from given (i) row is attacked by any queen placed in previous rows 
    // params:
    //      i - row
    // return:
    //      true - attacked
    //      false - not attacked
    bool IsAttacked(int i);

    // try to place the queen in given row (i)
    // params:
    //      i - row
    void TryPlace(int i);

    // runs nQueens for given n
    // params:
    //      param - pointer to size of table (nxn) and number of queens to place
    // return:
    //      0 - successful
    //      <>0 - unsuccessful
    virtual int Run(void* param = NULL);
};
