#include <gtest/gtest.h>

#include <string>

#include "../src/engine/Value.hpp"

class CastingTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

TEST_F(CastingTest, CastingToBoolTest) {
    ASSERT_EQ(Value(0).get_bool(), false);
    ASSERT_EQ(Value(-12).get_bool(), true);
    ASSERT_EQ(Value().get_bool(), false);
    ASSERT_EQ(Value("0").get_bool(), false);
    ASSERT_EQ(Value("fAlSE").get_bool(), false);
    ASSERT_EQ(Value("cat").get_bool(), true);
}

TEST_F(CastingTest, CastingToStringTest) {
    ASSERT_EQ(Value(-0.001).get_string(), "-0.001");
    ASSERT_EQ(Value(std::pow(10, 22)).get_string(), "Infinity");
    ASSERT_EQ(Value(-std::pow(10, 22)).get_string(), "-Infinity");
    ASSERT_EQ(Value(std::asin(10)).get_string(), "NaN");
    ASSERT_EQ(Value(true).get_string(), "true");
    ASSERT_EQ(Value(false).get_string(), "false");
}

TEST_F(CastingTest, CastingToNumberTest) {
    ASSERT_EQ(Value("abc").get_number(), 0);
    ASSERT_EQ(Value("true").get_number(), 1);
    ASSERT_EQ(Value("false").get_number(), 0);
    ASSERT_EQ(Value("123").get_number(), 123);
    ASSERT_EQ(Value("82,589,933").get_number(), 82589933);
}