#include "NQueensTest.h"

void NQueensTest::setUp()
{
    uniqueSolution = new CUniqueSolution();
    nQueens = new CNQueens(uniqueSolution, this);
}

void NQueensTest::tearDown()
{
    delete uniqueSolution;
    delete nQueens;
}

void NQueensTest::NQueensIsAttackedTest()
{
    int column[5] = {0, 2, 4, 3, 2};
    nQueens->n = 5;
    nQueens->column = column;

    CPPUNIT_ASSERT(!nQueens->IsAttacked(2));
    CPPUNIT_ASSERT(nQueens->IsAttacked(3));
    CPPUNIT_ASSERT(nQueens->IsAttacked(4));
}

void NQueensTest::NQueensTryPlaceTest()
{
    nQueens->n = 10;
    nQueens->column = new int[10];
    nQueens->TryPlace(0);

    CPPUNIT_ASSERT_EQUAL(724, nQueens->totalSolutionsNo);
    CPPUNIT_ASSERT_EQUAL(92, nQueens->uniqueSolutionsNo);

    delete[] nQueens->column;
}

void NQueensTest::NQueensSolveTest()
{
    nQueens->n = 10;
    nQueens->column = new int[10];
    nQueens->Solve();

    CPPUNIT_ASSERT_EQUAL(724, nQueens->totalSolutionsNo);
    CPPUNIT_ASSERT_EQUAL(92, nQueens->uniqueSolutionsNo);

    delete[] nQueens->column;
}
    
void NQueensTest::NQueensRunTest()
{
    int n;

    n = 1;
    nQueens->Run(&n);

    n = 2;
    nQueens->Run(&n);

    n = 3;
    nQueens->Run(&n);

    n = 4;
    nQueens->Run(&n);

    n = 5;
    nQueens->Run(&n);

    n = 6;
    nQueens->Run(&n);

    n = 7;
    nQueens->Run(&n);

    n = 8;
    nQueens->Run(&n);

    n = 9;
    nQueens->Run(&n);

    n = 10;
    nQueens->Run(&n);
}

int NQueensTest::Run(void* param)
{
    ResultsCollectorParam* result = (ResultsCollectorParam*) param;
    switch(result->n)
    {
        case 1 :
            CPPUNIT_ASSERT_EQUAL(1, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(1, result->uniqueSolutionsNo);
            break;
        case 2 :
            CPPUNIT_ASSERT_EQUAL(0, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(0, result->uniqueSolutionsNo);
            break;
        case 3 :
            CPPUNIT_ASSERT_EQUAL(0, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(0, result->uniqueSolutionsNo);
            break;
        case 4 :
            CPPUNIT_ASSERT_EQUAL(2, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(1, result->uniqueSolutionsNo);
            break;
        case 5 :
            CPPUNIT_ASSERT_EQUAL(10, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(2, result->uniqueSolutionsNo);
            break;
        case 6 :
            CPPUNIT_ASSERT_EQUAL(4, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(1, result->uniqueSolutionsNo);
            break;
        case 7 :
            CPPUNIT_ASSERT_EQUAL(40, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(6, result->uniqueSolutionsNo);
            break;
        case 8 :
            CPPUNIT_ASSERT_EQUAL(92, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(13, result->uniqueSolutionsNo);
            break;
        case 9 :
            CPPUNIT_ASSERT_EQUAL(352, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(46, result->uniqueSolutionsNo);
            break;
        case 10 :
            CPPUNIT_ASSERT_EQUAL(724, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(92, result->uniqueSolutionsNo);
            break;
        case 11 :
            CPPUNIT_ASSERT_EQUAL(2680, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(341, result->uniqueSolutionsNo);
            break;
        case 12 :
            CPPUNIT_ASSERT_EQUAL(14200, result->totalSolutionsNo);
            CPPUNIT_ASSERT_EQUAL(1796, result->uniqueSolutionsNo);
            break;
    }

    return 0;
}
