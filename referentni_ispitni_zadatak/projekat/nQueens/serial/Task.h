#pragma once

#include <stdio.h>

// class with virtual run method
// intended to be inherited by any class representing a "task"
class CTask
{
public:
    CTask(void);
    virtual ~CTask(void);
    virtual int Run(void* param = NULL) = 0;
};
