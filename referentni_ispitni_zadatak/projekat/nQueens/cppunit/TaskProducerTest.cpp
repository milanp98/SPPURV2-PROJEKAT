#include "TaskProducerTest.h"

void TaskProducerTest::setUp(){
    inFile.open(TASK_PRODUCER_TEST_0);
}

void TaskProducerTest::tearDown()
{
    inFile.close();
}

void TaskProducerTest::TaskProducerRunTest()
{
    CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE("Test file is not opened.", inFile.is_open());
    CTaskProducer taskProducer(TASK_PRODUCER_TEST_0, this);
    taskProducer.Run();
}

int TaskProducerTest::Run(void* param)
{
    int ref;
    inFile>>ref;

    int real = *(int*)param;

    CPPUNIT_ASSERT_EQUAL(ref, real);

    CPPUNIT_ASSERT(real!=0);

    return 0;
}
