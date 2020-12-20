#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "tbb/task.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/spin_mutex.h"
#include "tbb/concurrent_queue.h"

#include "UniqueSolutionP.h"
#include "ResultsCollectorP.h"

using namespace tbb;
using namespace std;

// class for solving n-queens problem
class CNQueensP : public task
{
private:
	int uniqueSolutionsNo;                                  // number of unique solutions
	int totalSolutionsNo;                                   // number of all solutions
    concurrent_queue<int*> queue;                           // queue of found solutions (to pass them to CUniqueSolutionP task)
    concurrent_queue<ResultsCollectorParam*>* result_queue; // queue with found results (to pass result to CResultsCollectorP task)
public:
	int n;                          // n parameter from n-queens problem (size of table nxn, number of queens)

    // constructor
    // params:
    //      n - size of table (nxn) and number of queens to place
    //      result_queue - pointer to queue with found results (to pass result to CResultsCollectorP task)
    CNQueensP(int n, concurrent_queue<ResultsCollectorParam*>* result_queue);

    // destructor
    ~CNQueensP(void);

    // init and start algorithm
    void Solve();

    // print results
    void Print();

    // makes and spowns CUniqueSolutionP task
    // calls Solve method to start algorithm
    // adds NULL to queue in order to signal CUniqueSolutionP task to finish
    // waits for CUniqueSolutionP task to finish
    // passes result to CResultsCollectorP task through result_queue
    task* execute();
};

// check if the queen from given (i) row is attacked by any queen placed in previous rows 
// params:
//      column - pointer to buffer with set queens
//      i - row
//      n - table size (buffer size), number of queens
// return:
//      true - attacked
//      false - not attacked
bool IsAttacked(int* column, int i, int n);

// try to place the queen in given row (i)
// params:
//      column - pointer to buffer with set queens
//      i - row
//      n - table size (buffer size), number of queens
//      totalSolutionsNo - pointer to number of total solutions
//      queue - pointer to queue of found solutions (to pass them to CUniqueSolutionP task)
void TryPlace(int* column, int i, int n, int* totalSolutionsNo, concurrent_queue<int*>* queue);

// class (functor) - body of parallel_for loop in  
class SetQueens {
public:
    int n;                          // table size
    int* totalSolutionsNo;          // pointer to number of solutions
    concurrent_queue<int*>* queue;  // pointer to queue of found solutions (to pass them to CUniqueSolutionP task)

    // constructor
    // param:
    //      n                - table size
    //      totalSolutionsNo - pointer to number of solutions
    //      queue            - pointer to queue of found solutions (to pass them to CUniqueSolutionP task)
    SetQueens(int n, int* totalSolutionsNo, concurrent_queue<int*>* queue) : n(n), totalSolutionsNo(totalSolutionsNo), queue(queue) {};

    // body
    // makes buffer for placing queens for each passed column of first row
    // calls TryPlace to place queens in remaining rows 
	void operator()( const blocked_range<size_t>& r ) const;
};
