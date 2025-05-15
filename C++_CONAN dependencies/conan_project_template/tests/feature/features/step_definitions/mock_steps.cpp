#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cucumber-cpp/autodetect.hpp>

#include <memory>

namespace
{

using cucumber::ScenarioScope;

class IFoo
{
public:
	virtual ~IFoo() {};
	virtual void foo() const = 0;
};

class Mock_Foo : public IFoo
{
public:
	MOCK_CONST_METHOD0(foo, void());
};

struct MockCtx
{
    std::shared_ptr<Mock_Foo> mock;
};

GIVEN("^a mock class with method foo$") {
	ScenarioScope<MockCtx> context{};
    context->mock = std::make_shared<Mock_Foo>();
}

GIVEN("^the tests expects that foo is called once$") {
	ScenarioScope<MockCtx> context{};
	EXPECT_CALL(*context->mock, foo());
}

WHEN("^foo is called on the mock$") {
	ScenarioScope<MockCtx> context{};
	context->mock->foo();
}

THEN("^the test should pass$") {
	ScenarioScope<MockCtx> context{};
	ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(context->mock.get()));
}

}
