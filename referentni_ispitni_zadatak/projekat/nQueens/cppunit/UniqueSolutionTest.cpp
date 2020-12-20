#include "UniqueSolutionTest.h"

void UniqueSolutionTest::setUp()
{
}

void UniqueSolutionTest::tearDown()
{
}


void UniqueSolutionTest::UniqueSolutionRotateTest()
{
    int columnIn[5] = {4, 2, 0, 3, 1};
    int columnOut[5];

    int columnExpected[5] = {2, 0, 3, 1, 4};

    uniqueSolution.Rotate(columnOut, columnIn, 5);
    CPPUNIT_ASSERT(memcmp(columnOut, columnExpected, 5)==0);
}

void UniqueSolutionTest::UniqueSolutionSymetreTest()
{
    int columnIn[5] = {4, 2, 0, 3, 1};
    int columnOut[5];

    int columnExpected[5] = {1, 3, 0, 2, 4};

    uniqueSolution.Symetre(columnOut, columnIn, 5);
    CPPUNIT_ASSERT(memcmp(columnOut, columnExpected, 5)==0);
}

void UniqueSolutionTest::UniqueSolutionRunTest()
{
    int uniqueSolutionsNo = 0;
    int column[5];

    UniqueSolutionParam param;
    param.n = 5;
    param.uniqueSolutionsNo = &uniqueSolutionsNo;
    param.column = column;
    
    column[0] = 4;
    column[1] = 2;
    column[2] = 0;
    column[3] = 3;
    column[4] = 1;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(0, uniqueSolutionsNo);

    column[0] = 2;
    column[1] = 0;
    column[2] = 3;
    column[3] = 1;
    column[4] = 4;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(0, uniqueSolutionsNo);

    column[0] = 3;
    column[1] = 1;
    column[2] = 4;
    column[3] = 2;
    column[4] = 0;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(0, uniqueSolutionsNo);

    column[0] = 0;
    column[1] = 3;
    column[2] = 1;
    column[3] = 4;
    column[4] = 2;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(0, uniqueSolutionsNo);

    column[0] = 0;
    column[1] = 2;
    column[2] = 4;
    column[3] = 1;
    column[4] = 3;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(1, uniqueSolutionsNo);

    column[0] = 4;
    column[1] = 1;
    column[2] = 3;
    column[3] = 0;
    column[4] = 2;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(1, uniqueSolutionsNo);

    column[0] = 1;
    column[1] = 3;
    column[2] = 0;
    column[3] = 2;
    column[4] = 4;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(1, uniqueSolutionsNo);

    column[0] = 2;
    column[1] = 4;
    column[2] = 1;
    column[3] = 3;
    column[4] = 0;
    uniqueSolution.Run(&param);
    CPPUNIT_ASSERT_EQUAL(1, uniqueSolutionsNo);
}
