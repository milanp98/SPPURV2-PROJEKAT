#include "MainProgram.h"

#include <iostream>
#include <stdio.h>

#include "tbb/tick_count.h"

#include "ResultsCollector.h"
#include "UniqueSolution.h"
#include "NQueens.h"
#include "TaskProducer.h"

using namespace tbb;
using namespace std;

// prints programs title
void printTitle()
{
    cout<<"**********n-Queens serial**********";
	cout<<endl;
	cout<<endl;
}


// prints program usage info
void printUsage()
{
    cout<<endl;
    cout<<"Execute program like: \"serial.exe <input_file_name> <output_file_name>\"."<<endl;
    cout<<endl;
    cout<<endl;
}


// argv[1] - in file name
// argv[2] - out file name
int mainSerial(int argc, char* argv[])
{
    char* inFileName;
    char* outFileName;

    printTitle();
	
    if(argc!=3)
    {
        cout<<"Error. Wrong number of arguments passed."<<endl;
        printUsage();
        return -1;
    }

    inFileName = argv[1];
    outFileName = argv[2];

    CResultsCollector* resultsCollector = new CResultsCollector(outFileName);
    CUniqueSolution* uniqueSolution = new CUniqueSolution();
    CNQueens* nQueens = new CNQueens((CTask*)uniqueSolution, (CTask*)resultsCollector);
    CTaskProducer* taskProducer = new CTaskProducer(inFileName, (CTask*)nQueens);

    tick_count startTime = tick_count::now();
    // run program
    taskProducer->Run();
    tick_count endTime = tick_count::now();

	cout << endl << "Execution time: " << (endTime-startTime).seconds()*1000 << "ms." << endl;
    cout << endl;
    cout << endl;

    // free memory
    delete taskProducer;
    delete nQueens;
    delete uniqueSolution;

    return 0;
}
