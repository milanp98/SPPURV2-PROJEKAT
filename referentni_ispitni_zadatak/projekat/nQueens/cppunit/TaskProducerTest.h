#ifndef TaskProducerTestH
#define TaskProducerTestH

#include <cppunit/extensions/HelperMacros.h>

#include "TaskProducer.h"
#include "Task.h"
#include "PathConstants.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

class TaskProducerTest : public CPPUNIT_NS::TestFixture, public CTask
{
    CPPUNIT_TEST_SUITE( TaskProducerTest );
    CPPUNIT_TEST( TaskProducerRunTest );
    CPPUNIT_TEST_SUITE_END();
  
private:
    ifstream inFile;
    
public:
    void setUp();
    void tearDown();

    // additional function for testing task producer
    // reds coresponding line of input file and compares it to passed value
    virtual int Run(void* param = NULL);
    
protected:
    // tests if passed function is called for each line (param) of input file
    void TaskProducerRunTest();

};

#endif
