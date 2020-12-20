#ifndef ResultsCollectorTestH
#define ResultsCollectorTestH

#include <cppunit/extensions/HelperMacros.h>

#include "ResultsCollector.h"
#include "PathConstants.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

class ResultsCollectorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ResultsCollectorTest );
    CPPUNIT_TEST( ResultsCollectorRunTest );
    CPPUNIT_TEST_SUITE_END();
  
private:
    
public:
    void setUp();
    void tearDown();
    
protected:

    // tests if a line is written to output file each time the run method of ResultsCollector is called
    void ResultsCollectorRunTest();

};

#endif
