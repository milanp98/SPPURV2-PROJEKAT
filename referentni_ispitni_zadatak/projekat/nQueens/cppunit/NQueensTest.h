#ifndef NQueensTestH
#define NQueensTestH

#include <cppunit/extensions/HelperMacros.h>

#include "NQueens.h"
#include "UniqueSolution.h"
#include "ResultsCollector.h"
#include "Task.h"
#include "PathConstants.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>

using namespace std;

class NQueensTest : public CPPUNIT_NS::TestFixture, public CTask
{
    CPPUNIT_TEST_SUITE( NQueensTest );
    CPPUNIT_TEST( NQueensIsAttackedTest );
    CPPUNIT_TEST( NQueensTryPlaceTest );
    CPPUNIT_TEST( NQueensSolveTest );
    CPPUNIT_TEST( NQueensRunTest );
    CPPUNIT_TEST_SUITE_END();
  
private:
    CNQueens* nQueens;                  // pointer to object of tested class
    CUniqueSolution* uniqueSolution;    // poointer to task used for nQueens

public:
    void setUp();
    void tearDown();
    
    // additional function for testing NQueens
    // reads passed parameter and checks if correct result is passed, acording to parameters passed to NQueens run method
    virtual int Run(void* param = NULL);
    
protected:

    // tests if IsAttacked returns true when attacked situation is passed, and false otherwise
    void NQueensIsAttackedTest();

    // checks if TryPlace() method gives correct number of solutions for passed argument
    void NQueensTryPlaceTest();
    
    // checks if Solve() method gives correct number of solutions for passed argument
    void NQueensSolveTest();
    
    // tests run method; results are captured through underlayed this->run method
    void NQueensRunTest();

};

#endif
