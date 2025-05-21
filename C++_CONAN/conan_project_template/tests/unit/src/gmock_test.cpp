#include <gmock/gmock.h>

class IFoo
{
public:
    virtual ~IFoo()
    {}

    virtual void foo() const = 0;

    virtual void bar() const = 0;
};


class MockFoo : public IFoo
{
public:
    MOCK_CONST_METHOD0(foo, void());

    MOCK_CONST_METHOD0(bar, void());
};

class Testee
{
public:
    explicit Testee(const IFoo& foo)
            : my_foo(foo)
    {
    }

    void call_foo() const
    {
        my_foo.foo();
    }

private:
    const IFoo& my_foo;
};

namespace
{

// This test is used to show how google mock can be used
    TEST(A_testee_depending_on_a_mock, should_call_the_mock)
    {
        MockFoo foo{};
        Testee testee{foo};
        EXPECT_CALL(foo, foo());

        testee.call_foo();
    }

} //namespace
