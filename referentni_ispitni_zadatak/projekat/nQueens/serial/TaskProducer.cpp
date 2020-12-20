#include "TaskProducer.h"

CTaskProducer::CTaskProducer(char* inFileName,  CTask* task)
{
    this->inFileName = inFileName;
    this->task = task;
    inFile.open(inFileName);
    if(!inFile.is_open())
    {
        cout<<"Input file \""<<inFileName<<"\" could not be opened."<<endl;
        cout<<endl;
    }
}

CTaskProducer::~CTaskProducer(void)
{
    inFile.close();
}

int CTaskProducer::Run(void* param)
{
    int n;

    if(!inFile.is_open())
    {
        cout<<"Input file is not opened."<<endl;
        cout<<endl;
        return -1;
    }

    while(!inFile.eof())
    {
        inFile>>n;
        if(task->Run(&n))
        {
            cout<<"Task function execution failed with parameter \""<<n<<"\"."<<endl;
            cout<<endl;
            return -1;
        }
    }

    return 0;
}
