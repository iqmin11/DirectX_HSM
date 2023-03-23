#include "TestLevel.h"
#include "TestActor.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Loading()
{
	std::shared_ptr<TestActor> AcTest = CreateActor<TestActor>("TestActor");
}
