#include <gtest/gtest.h>
#include "dummy.h"

namespace
{

    using CppTemplate::Dummy;

    TEST(A_default_Dummy, should_be_speechless)
    {
        Dummy dummy{};
        ASSERT_TRUE(dummy.speechless());
    }

    TEST(A_english_Dummy, should_not_be_speechless)
    {
        Dummy dummy{"Hello", "World"};
        ASSERT_FALSE(dummy.speechless());
    }

    TEST(A_english_Dummy, should_speak_the_correct_language)
    {
        Dummy dummy{"Hello", "World"};
        ASSERT_STREQ("Hello World", dummy.say_hello().c_str());
    }

} //namespace
