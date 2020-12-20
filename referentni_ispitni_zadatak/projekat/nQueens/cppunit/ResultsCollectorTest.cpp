#include "ResultsCollectorTest.h"

void ResultsCollectorTest::setUp(){
}

void ResultsCollectorTest::tearDown()
{
}

// Test list of files
void ResultsCollectorTest::ResultsCollectorRunTest()
{
    ResultsCollectorParam param;
    CResultsCollector resultsCollector(RESULT_COLLECTOR_RUN_TEST);

    param.n = 1;
    param.totalSolutionsNo = 1;
    param.uniqueSolutionsNo = 1;
    resultsCollector.Run(&param);

    param.n = 2;
    param.totalSolutionsNo = 0;
    param.uniqueSolutionsNo = 0;
    resultsCollector.Run(&param);

    param.n = 3;
    param.totalSolutionsNo = 0;
    param.uniqueSolutionsNo = 0;
    resultsCollector.Run(&param);

    param.n = 4;
    param.totalSolutionsNo = 2;
    param.uniqueSolutionsNo = 1;
    resultsCollector.Run(&param);

    param.n = 5;
    param.totalSolutionsNo = 10;
    param.uniqueSolutionsNo = 2;
    resultsCollector.Run(&param);

    param.n = 6;
    param.totalSolutionsNo = 4;
    param.uniqueSolutionsNo = 1;
    resultsCollector.Run(&param);

    param.n = 7;
    param.totalSolutionsNo = 40;
    param.uniqueSolutionsNo = 6;
    resultsCollector.Run(&param);

    param.n = 8;
    param.totalSolutionsNo = 92;
    param.uniqueSolutionsNo = 13;
    resultsCollector.Run(&param);

    param.n = 9;
    param.totalSolutionsNo = 352;
    param.uniqueSolutionsNo = 46;
    resultsCollector.Run(&param);

    param.n = 10;
    param.totalSolutionsNo = 724;
    param.uniqueSolutionsNo = 92;
    resultsCollector.Run(&param);

    param.n = 11;
    param.totalSolutionsNo = 2680;
    param.uniqueSolutionsNo = 341;
    resultsCollector.Run(&param);

    param.n = 12;
    param.totalSolutionsNo = 14200;
    param.uniqueSolutionsNo = 1796;
    resultsCollector.Run(&param);

    ifstream refFile;
    ifstream testFile;

    refFile.open(RESULT_COLLECTOR_RUN_TEST_REF);
    testFile.open(RESULT_COLLECTOR_RUN_TEST);

    refFile.seekg(0, ios_base::end);
    int refFileSize = refFile.tellg();
    refFile.seekg(0, ios_base::beg);

    testFile.seekg(0, ios_base::end);
    int testFileSize = testFile.tellg();
    testFile.seekg(0, ios_base::beg);

    CPPUNIT_ASSERT_EQUAL(testFileSize, refFileSize);

    char* refFileBuf = new char[refFileSize];
    char* testFileBuf = new char[testFileSize];

    refFile.read(refFileBuf, refFileSize);
    testFile.read(testFileBuf, testFileSize);

    bool equal = memcmp(refFileBuf, testFileBuf, refFileSize)==0;

    delete[] refFileBuf;
    delete[] testFileBuf;

    CPPUNIT_ASSERT(equal);
}
