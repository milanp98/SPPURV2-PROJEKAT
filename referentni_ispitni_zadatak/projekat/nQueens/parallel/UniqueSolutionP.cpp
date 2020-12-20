#include "UniqueSolutionP.h"

CUniqueSolutionP::CUniqueSolutionP(int n, concurrent_queue<int*>* queue, int *uniqueSolutionsNo) : n(n), queue(queue), uniqueSolutionsNo(uniqueSolutionsNo)
{
    in90 = new int[n];
    in180 = new int[n];
    in270 = new int[n];
    sim = new int[n];
    sim90 = new int[n];
    sim180 = new int[n];
    sim270 = new int[n];
}

CUniqueSolutionP::~CUniqueSolutionP(void)
{
    delete in90;
    delete in180;
    delete in270;
    delete sim;
    delete sim90;
    delete sim180;
    delete sim270;
}

void CUniqueSolutionP::Symetre(int* out, int* in, int n)
{
    for(int i = 0; i<n; i++)
    {
        out[i] = in[n-i-1];
    }

}

void CUniqueSolutionP::Rotate(int* out, int* in, int n)
{
    for(int i = 0; i<n; i++)
    {
        out[in[i]] = n-1-i;
    }

}

int CUniqueSolutionP::Run(int *column)
{

    Rotate(in90, column, n);
    Rotate(in180, in90, n);
    Rotate(in270, in180, n);
    Symetre(sim, column, n);
    Rotate(sim90, sim, n);
    Rotate(sim180, sim90, n);
    Rotate(sim270, sim180, n);

    if(!( memcmp(column, in90, n) > 0 ||
         memcmp(column, in180, n) > 0 ||
         memcmp(column, in270, n) > 0 ||
         memcmp(column, sim, n) > 0 ||
         memcmp(column, sim90, n) > 0 ||
         memcmp(column, sim180, n) > 0 ||
         memcmp(column, sim270, n) > 0 ) )
    {
        (*(uniqueSolutionsNo))++;
    }

    return 0;
}

task* CUniqueSolutionP::execute()
{
    int* column;

    while(true)
    {
        // take next
        while(!queue->try_pop(column))
        {
            // give up time slice
            std::this_thread::sleep_for(tbb::tick_count::interval_t(double(10)/1000));
        }
        if(column==NULL)
        {
            break;
        }
        else
        {
            Run(column);
        }
    }

    //if(queue->try_pop(column))
    //{
    //    if(column!=NULL)
    //    {
    //        Run(column);
    //        recycle_to_reexecute();
    //    }
    //}
    //else
    //{
    //    recycle_to_reexecute();
    //}

    return NULL;
}
