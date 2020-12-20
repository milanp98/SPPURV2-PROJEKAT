#include "ResultsCollectorP.h"

CResultsCollectorP::CResultsCollectorP(char* outFileName, concurrent_queue<ResultsCollectorParam*>* queue) : queue(queue)
{
    this->outFileName = outFileName;
    outFile.open(outFileName);
    if(!outFile.is_open())
    {
        cout<<"Output file \""<<outFileName<<"\" could not be opened."<<endl;
        cout<<endl;
    }
    else
    {
        outFile<<"N\t"<<"TOTAL\t"<<"UNIQUE"<<endl;
    }
}

CResultsCollectorP::~CResultsCollectorP(void)
{
    outFile.close();
}

task* CResultsCollectorP::execute()
{
    ResultsCollectorParam* params;

    while(true)
    {
        // take next
        while(!queue->try_pop(params))
        {
            // give up time slice
            std::this_thread::sleep_for(tbb::tick_count::interval_t(double(1)/1000));
        }
        if(params==NULL)
        {
            break;
        }
        else
        {
            outFile<<params->n<<":\t"<<params->totalSolutionsNo<<"\t"<<params->uniqueSolutionsNo<<endl;
	        outFile<<endl;
	        outFile<<endl;
        }
    }

    //if(queue->try_pop(params))
    //{
    //    if(params!=NULL)
    //    {
    //        outFile<<params->n<<":\t"<<params->totalSolutionsNo<<"\t"<<params->uniqueSolutionsNo<<endl;
	   //     outFile<<endl;
	   //     outFile<<endl;
    //        recycle_to_reexecute();
    //    }
    //}
    //else
    //{
    //    recycle_to_reexecute();
    //}

    return NULL;
}
