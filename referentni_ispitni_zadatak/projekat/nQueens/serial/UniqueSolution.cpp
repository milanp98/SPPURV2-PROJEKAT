#include "UniqueSolution.h"

CUniqueSolution::CUniqueSolution(void)
{
}

CUniqueSolution::~CUniqueSolution(void)
{
}

void CUniqueSolution::Symetre(int* out, int* in, int n)
{
    for(int i = 0; i<n; i++)
    {
        out[i] = in[n-i-1];
    }

}

void CUniqueSolution::Rotate(int* out, int* in, int n)
{
    for(int i = 0; i<n; i++)
    {
        out[in[i]] = n-1-i;
    }

}

int CUniqueSolution::Run(void *param)
{
    UniqueSolutionParam params = *(UniqueSolutionParam*)param;
    int* in90 = new int[params.n];
    int* in180 = new int[params.n];
    int* in270 = new int[params.n];
    int* sim = new int[params.n];
    int* sim90 = new int[params.n];
    int* sim180 = new int[params.n];
    int* sim270 = new int[params.n];

    Rotate(in90, params.column, params.n);
    Rotate(in180, in90, params.n);
    Rotate(in270, in180, params.n);
    Symetre(sim, params.column, params.n);
    Rotate(sim90, sim, params.n);
    Rotate(sim180, sim90, params.n);
    Rotate(sim270, sim180, params.n);

    if(!( memcmp(params.column, in90, params.n) > 0 ||
         memcmp(params.column, in180, params.n) > 0 ||
         memcmp(params.column, in270, params.n) > 0 ||
         memcmp(params.column, sim, params.n) > 0 ||
         memcmp(params.column, sim90, params.n) > 0 ||
         memcmp(params.column, sim180, params.n) > 0 ||
         memcmp(params.column, sim270, params.n) > 0 ) )
    {
        (*(params.uniqueSolutionsNo))++;
    }

    delete in90;
    delete in180;
    delete in270;
    delete sim;
    delete sim90;
    delete sim180;
    delete sim270;

    return 0;
}