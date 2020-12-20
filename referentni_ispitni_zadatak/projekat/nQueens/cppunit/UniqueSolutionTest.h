#ifndef UniqueSolutionTestH
#define UniqueSolutionTestH

#include <cppunit/extensions/HelperMacros.h>

#include "UniqueSolution.h"
#include "PathConstants.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

class UniqueSolutionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( UniqueSolutionTest );
    CPPUNIT_TEST( UniqueSolutionRotateTest );
    CPPUNIT_TEST( UniqueSolutionSymetreTest );
    CPPUNIT_TEST( UniqueSolutionRunTest );
    CPPUNIT_TEST_SUITE_END();
  
private:
    CUniqueSolution uniqueSolution;
    
public:
    void setUp();
    void tearDown();
    
protected:
    // tests rotation by giving input buffer and checking if output bufer is rotated as expected
    void UniqueSolutionRotateTest();

    // tests symetre by giving input buffer and checking if output bufer is processed as expected
    void UniqueSolutionSymetreTest();

    // runs uniqueSolution  run method for whole set of solutions from the same class, and checks if onlyu one of them is considered as unique
    void UniqueSolutionRunTest();

};

#endif
