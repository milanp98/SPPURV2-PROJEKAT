#include "ResultsCollector.h"

CResultsCollector::CResultsCollector(char* outFileName)
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

CResultsCollector::~CResultsCollector(void)
{
    outFile.close();
}

int CResultsCollector::Run(void* param)
{
    ResultsCollectorParam params = *(ResultsCollectorParam*)param;

    outFile<<params.n<<":\t"<<params.totalSolutionsNo<<"\t"<<params.uniqueSolutionsNo<<endl;
	outFile<<endl;
	outFile<<endl;

    return 0;
}
