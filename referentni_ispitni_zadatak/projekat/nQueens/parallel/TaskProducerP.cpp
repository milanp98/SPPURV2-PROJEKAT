#include "TaskProducerP.h"

CTaskProducerP::CTaskProducerP(char* inFileName, char* outFileName)
{
    this->inFileName = inFileName;
    this->outFileName = outFileName;
    inFile.open(inFileName);
    if(!inFile.is_open())
    {
        cout<<"Input file \""<<inFileName<<"\" could not be opened."<<endl;
        cout<<endl;
    }
}

CTaskProducerP::~CTaskProducerP(void)
{
    inFile.close();
}

task* CTaskProducerP::execute()
{
    int n;

    if(!inFile.is_open())
    {
        cout<<"Input file is not opened."<<endl;
        cout<<endl;
        return NULL;
    }

    CResultsCollectorP* resultCollector = new( tbb::task::allocate_child() ) CResultsCollectorP(outFileName, &result_queue);
    resultCollector->set_ref_count(0);
    task::spawn(*resultCollector);

    while(!inFile.eof())
    {
        inFile>>n;

        CNQueensP *nQueens = new( tbb::task::allocate_child() ) CNQueensP(n, &result_queue);
        nQueens->set_ref_count(1);
        this->increment_ref_count();
        task::spawn(*nQueens);
    }

    this->wait_for_all();

    // send signal to resultCollector (all nQueens processed)
    result_queue.push(NULL);

    // wait for resultCollector to finish
    this->set_ref_count(2);
    this->wait_for_all();


    return NULL;
}
