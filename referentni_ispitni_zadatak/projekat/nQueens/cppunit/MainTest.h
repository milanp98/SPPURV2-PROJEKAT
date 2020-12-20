#ifndef MainTestH
#define MainTestH

#include <cppunit/extensions/HelperMacros.h>

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

#include "PathConstants.h"

#include "MainProgram.h"
#include "MainProgramP.h"

using namespace std;

class MainTests : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MainTests );
    CPPUNIT_TEST( SerialAndParallelCmp );
    CPPUNIT_TEST_SUITE_END();
  
private:
    
public:
    void setUp();
    void tearDown();
    
protected:
    void SerialAndParallelCmp();

};

#endif