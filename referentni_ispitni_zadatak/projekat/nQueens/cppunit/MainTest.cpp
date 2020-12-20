#include "MainTest.h"

void MainTests::setUp()
{
}

void MainTests::tearDown()
{
}

void MainTests::SerialAndParallelCmp()
{
    cout<<endl;

    char* argvs[] = {"", MAIN_TEST_SERIAL_AND_PARALLEL_CMP_IN, MAIN_TEST_SERIAL_AND_PARALLEL_CMP_SOUT};
    mainSerial(3, argvs);

    cout<<endl;

    char* argvp[] = {"", MAIN_TEST_SERIAL_AND_PARALLEL_CMP_IN, MAIN_TEST_SERIAL_AND_PARALLEL_CMP_POUT};
    mainParallel(3, argvp);

    cout<<endl;

    ifstream refFile;
    ifstream testFile;

    refFile.open(MAIN_TEST_SERIAL_AND_PARALLEL_CMP_SOUT);
    testFile.open(MAIN_TEST_SERIAL_AND_PARALLEL_CMP_POUT);

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

    int equal = memcmp(refFileBuf, testFileBuf, refFileSize);

    delete[] refFileBuf;
    delete[] testFileBuf;

//    CPPUNIT_ASSERT_EQUAL(0, equal);
}
