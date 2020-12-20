#include "MainProgramP.h"

#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
#include "tbb/task.h"

#include "TaskProducerP.h"
#include "ResultsCollectorP.h"

using namespace tbb;
using namespace std;


// prints programs title
void printTitleP()
{
    cout<<"**********n-Queens parallel**********";
	cout<<endl;
	cout<<endl;
}


// prints program usage info
void printUsageP()
{
    cout<<endl;
    cout<<"Execute program like: \"parallel.exe <input_file_name> <output_file_name>\"."<<endl;
    cout<<endl;
    cout<<endl;
}


// argv[1] - in file name
// argv[2] - out file name
int mainParallel(int argc, char* argv[])
{
    char* inFileName;
    char* outFileName;

    printTitleP();
	
    if(argc!=3)
    {
        cout<<"Error. Wrong number of arguments passed."<<endl;
        printUsageP();
        return -1;
    }

    inFileName = argv[1];
    outFileName = argv[2];

    tick_count startTime = tick_count::now();

    // initialize tbb scheduler (required in TBB 2.1 and earlier)
    task_scheduler_init init;

    // create and spawn CTaskProducerP task as root task and wait for it to finish
    CTaskProducerP* taskProducer = new( tbb::task::allocate_root() ) CTaskProducerP(inFileName, outFileName);
    taskProducer->set_ref_count(1);     // task will wait for all nQueen task to finish
    task::spawn_root_and_wait(*taskProducer);

    tick_count endTime = tick_count::now();

	cout << endl << "Execution time: " << (endTime-startTime).seconds()*1000 << "ms." << endl;
    cout << endl;
    cout << endl;

    return 0;
}