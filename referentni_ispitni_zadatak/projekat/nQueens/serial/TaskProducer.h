#pragma once

#include <iostream>
#include <fstream>

#include "Task.h"

using namespace std;

// class for reading input file and producing NQueens tasks (calling these blocks)
class CTaskProducer : public CTask
{
    char* inFileName;   // input file name (set of task params)
    ifstream inFile;    // input file
    CTask* task;        // task to execute passing a param from single line of input file
public:

    // constructor
    // param:
    //      inFileName - input file name
    //      task - pointer to class derived from CTask that is executed for each parameter from input file
    CTaskProducer(char* inFileName, CTask* task);

    // destructor
    ~CTaskProducer(void);

    // reads input file and executes task's run method for each parameter passing it
    // param:
    //      param - not used
    virtual int Run(void* param = NULL);
};
