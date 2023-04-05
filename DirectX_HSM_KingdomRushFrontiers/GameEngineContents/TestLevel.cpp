#include "TestLevel.h"
#include "TestActor.h"

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Start()
{
	std::shared_ptr<TestActor> AcTest = CreateActor<TestActor>("TestActor");
}
