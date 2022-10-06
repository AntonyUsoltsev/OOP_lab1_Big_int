#include <iostream>
#include <utility>
#include "gtest/gtest.h"
#include "BigInt.h"

const int INT_MAX_LOCAL = 2147483647;
const int INT_MIN_LOCAL = -2147483648;

const std::string INT_MAX_LOCAL_STRING = "2147483647";
const std::string INT_MIN_LOCAL_STRING = "-2147483648";


struct StringArg {
    std::string val;
    std::string expected;

    StringArg(std::string val, std::string expected) : val(std::move(val)), expected(std::move(expected)) {}
};

struct BigIntPairArg {
    BigInt val1;
    BigInt val2;
    std::string expected;

    BigIntPairArg(const BigInt &val1, const BigInt &val2, std::string expected) :
            val1(val1), val2(val2), expected(std::move(expected)) {}
};


TEST(bigint_test, int_constructor) {
    ASSERT_EQ("2147483647", (std::string) BigInt(INT_MAX_LOCAL));
    ASSERT_EQ("-2147483648", (std::string) BigInt(INT_MIN_LOCAL));
}

class StringConstructorTest : public ::testing::TestWithParam<StringArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        StringConstructorTest,
        ::testing::Values(
                StringArg("-9223372036854775808", "-9223372036854775808"),
                StringArg("9223372036854775807", "9223372036854775807"),
                StringArg("0000002147483647", "2147483647"),
                StringArg("0000", "0"),
                StringArg("-0", "0")
        )
);

TEST_P(StringConstructorTest, string_constructor) {
    StringArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) BigInt(arg.val));
}

TEST(bigint_test, copy_constructor) {
    BigInt val1 = BigInt(INT_MAX_LOCAL);
    const BigInt &val2 = val1;
    ASSERT_EQ(INT_MAX_LOCAL_STRING, (std::string) val2);
}

TEST(bigint_test, copy_operator_self_assignment) {
    BigInt val1 = BigInt(INT_MAX_LOCAL);
    val1 = val1;
    ASSERT_EQ(INT_MAX_LOCAL_STRING, (std::string) val1);
}

TEST(bigint_test, bitwise_not) {
    BigInt val1 = BigInt(INT_MAX_LOCAL);
    ASSERT_EQ(INT_MIN_LOCAL_STRING, (std::string) ~val1);
}

TEST(bigint_test, postfix_unary_increment) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = val1++;
    ASSERT_EQ(1000, int(val2));
}

TEST(bigint_test, prefix_unary_increment) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = ++val1;
    ASSERT_EQ(1001, int(val2));
}

TEST(bigint_test, postfix_unary_decrement) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = val1--;
    ASSERT_EQ(1000, int(val2));
}

TEST(bigint_test, prefix_unary_decrement) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = --val1;
    ASSERT_EQ(999, int(val2));
}

class BigIntAdditionTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntAdditionTest,
        ::testing::Values(
                BigIntPairArg(BigInt("0"), BigInt("-0"), "0"),
                BigIntPairArg(BigInt("1000"), BigInt("1000"), "2000"),
                BigIntPairArg(BigInt("-1000"), BigInt("1000"), "0"),
                BigIntPairArg(BigInt("2147483647"), BigInt("1"), "2147483648"),
                BigIntPairArg(BigInt("2147483647"), BigInt("4294967296"), "6442450943")
        )
);

TEST_P(BigIntAdditionTest, assignment_addition) {
    BigIntPairArg arg = GetParam();
    arg.val1 += arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntAdditionTest, addition_addition) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 + arg.val2));
}

class BigIntSubtractionTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntSubtractionTest,
        ::testing::Values(
                BigIntPairArg(BigInt("0"), BigInt("-0"), "0"),
                BigIntPairArg(BigInt("1000"), BigInt("1000"), "0"),
                BigIntPairArg(BigInt("-1000"), BigInt("1000"), "-2000"),
                BigIntPairArg(BigInt("-1000"), BigInt("-1000"), "0"),
                BigIntPairArg(BigInt("2147483648"), BigInt("1"), "2147483647"),
                BigIntPairArg(BigInt("2147483647"), BigInt("4294967296"), "-2147483649"),
                BigIntPairArg(BigInt("4294967296"), BigInt("2147483647"), "2147483649")
        )
);

TEST_P(BigIntSubtractionTest, assignment_subtraction) {
    BigIntPairArg arg = GetParam();
    arg.val1 -= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntSubtractionTest, subtraction) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 - arg.val2));
}

class BigIntMultiplicationTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntMultiplicationTest,
        ::testing::Values(
                BigIntPairArg(BigInt("0"), BigInt("-0"), "0"),
                BigIntPairArg(BigInt("-10"), BigInt("-10"), "100"),
                BigIntPairArg(BigInt("1000"), BigInt("-1"), "-1000"),
                BigIntPairArg(BigInt("1234567"), BigInt("789"), "974073363"),
                BigIntPairArg(BigInt("2147483648"), BigInt("1"), "2147483648"),
                BigIntPairArg(BigInt("2147483647"), BigInt("3"), "6442450941")
        )
);

TEST_P(BigIntMultiplicationTest, assignment_multiplication) {
    BigIntPairArg arg = GetParam();
    arg.val1 *= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntMultiplicationTest, multiplication) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 * arg.val2));
}

class BigIntDivisionTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntDivisionTest,
        ::testing::Values(
                BigIntPairArg(BigInt("-10"), BigInt("-10"), "1"),
                BigIntPairArg(BigInt("1000"), BigInt("-1"), "-1000"),
                BigIntPairArg(BigInt("5000"), BigInt("5"), "1000"),
                BigIntPairArg(BigInt("5000"), BigInt("11"), "454"),
                BigIntPairArg(BigInt("4294967296"), BigInt("512"), "8388608")
        )
);

TEST_P(BigIntDivisionTest, assignment_division) {
    BigIntPairArg arg = GetParam();
    arg.val1 /= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntDivisionTest, division) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 / arg.val2));
}

class BigIntXorTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntXorTest,
        ::testing::Values(
                BigIntPairArg(BigInt("10"), BigInt("1"), "11"),
                BigIntPairArg(BigInt("1000"), BigInt("-1000"), "-16"),
                BigIntPairArg(BigInt("-1000"), BigInt("-1000"), "0"),
                BigIntPairArg(BigInt("54321"), BigInt("123"), "54346"),
                //BigIntPairArg(BigInt("54321"), BigInt("-123"), "-54348"), //Р”РѕРїРѕР»РЅРёС‚РµР»СЊРЅС‹Р№ РєРѕРґ
                //BigIntPairArg(BigInt("54321"), BigInt("-123"), "-54346"), //РџСЂСЏРјРѕР№ РєРѕРґ
                BigIntPairArg(BigInt("4294967296"), BigInt("512"), "4294967808")
        )
);

TEST_P(BigIntXorTest, assignment_xor_op) {
    BigIntPairArg arg = GetParam();
    arg.val1 ^= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntXorTest, xor_op) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 ^ arg.val2));
}

class BigIntModTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntModTest,
        ::testing::Values(
                BigIntPairArg(BigInt("1000"), BigInt("-6"), "4"),
                BigIntPairArg(BigInt("-1000"), BigInt("1000"), "0"),
                BigIntPairArg(BigInt("2147483647"), BigInt("2147483646"), "1"),
                BigIntPairArg(BigInt("4294967296"), BigInt("1023"), "4")
        )
);

TEST_P(BigIntModTest, assignment_mod) {
    BigIntPairArg arg = GetParam();
    arg.val1 %= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntModTest, mod) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 % arg.val2));
}

class BigIntAndTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntAndTest,
        ::testing::Values(
                BigIntPairArg(BigInt("10"), BigInt("1"), "0"),
                //BigIntPairArg(BigInt("1000"), BigInt("-1000"), "1000"), //РџСЂСЏРјРѕР№ РєРѕРґ
                //BigIntPairArg(BigInt("1000"), BigInt("-1000"), "8"), //Р”РѕРїРѕР»РЅРёС‚РµР»СЊРЅС‹Р№ РєРѕРґ
                BigIntPairArg(BigInt("-1000"), BigInt("-1000"), "-1000"),
                BigIntPairArg(BigInt("54321"), BigInt("123"), "49"),
                BigIntPairArg(BigInt("4294967296"), BigInt("512"), "0"),
                BigIntPairArg(BigInt("4294967295"), BigInt("512"), "512")
        )
);

TEST_P(BigIntAndTest, assignment_and) {
    BigIntPairArg arg = GetParam();
    arg.val1 &= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntAndTest, and) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 & arg.val2));
}

class BigIntOrTest : public ::testing::TestWithParam<BigIntPairArg> {
};

INSTANTIATE_TEST_SUITE_P(
        bigint_test,
        BigIntOrTest,
        ::testing::Values(
                BigIntPairArg(BigInt("10"), BigInt("1"), "11"),
                //BigIntPairArg(BigInt("1000"), BigInt("-1000"), "-1000"), //РџСЂСЏРјРѕР№ РєРѕРґ
                //BigIntPairArg(BigInt("1000"), BigInt("-1000"), "-8"), //Р”РѕРїРѕР»РЅРёС‚РµР»СЊРЅС‹Р№ РєРѕРґ
                BigIntPairArg(BigInt("-1000"), BigInt("-1000"), "-1000"),
                BigIntPairArg(BigInt("54321"), BigInt("123"), "54395"),
                BigIntPairArg(BigInt("4294967296"), BigInt("512"), "4294967808"),
                BigIntPairArg(BigInt("4294967295"), BigInt("512"), "4294967295")
        )
);

TEST_P(BigIntOrTest, assignment_or) {
    BigIntPairArg arg = GetParam();
    arg.val1 |= arg.val2;
    ASSERT_EQ(arg.expected, (std::string) arg.val1);
}

TEST_P(BigIntOrTest, and) {
    BigIntPairArg arg = GetParam();
    ASSERT_EQ(arg.expected, (std::string) (arg.val1 | arg.val2));
}

TEST(bigint_test, unary_minus) {
    BigInt val1("4294967296");
    ASSERT_EQ("-4294967296", (std::string) -val1);

    BigInt val2("-4294967296");
    ASSERT_EQ("4294967296", (std::string) -val2);
}

TEST(bigint_test, unary_plus) {
    BigInt val1("4294967296");
    ASSERT_EQ("4294967296", (std::string) +val1);

    BigInt val2("-4294967296");
    ASSERT_EQ("-4294967296", (std::string) +val2);
}

TEST(bigint_test, compare_test) {
    ASSERT_TRUE(BigInt("0") == BigInt("-0"));
    ASSERT_TRUE(BigInt("4294967296") == BigInt("4294967296"));

    ASSERT_TRUE(BigInt("4294967296") != BigInt("4294967295"));
    ASSERT_TRUE(BigInt("4294967296") != BigInt("-4294967296"));

    ASSERT_TRUE(BigInt("4294967296") > BigInt("4294967295"));
    ASSERT_TRUE(BigInt("4294967296") > BigInt("-4294967295"));
    ASSERT_TRUE(BigInt("-4294967294") > BigInt("-4294967295"));

    ASSERT_TRUE(BigInt("4294967295") < BigInt("4294967296"));
    ASSERT_TRUE(BigInt("-4294967295") < BigInt("4294967296"));
    ASSERT_TRUE(BigInt("-4294967295") < BigInt("-4294967294"));

    ASSERT_TRUE(BigInt("4294967296") <= BigInt("4294967296"));
    ASSERT_TRUE(BigInt("4294967296") >= BigInt("4294967296"));
}

TEST(bigint_test, size) {
    ASSERT_TRUE(BigInt("4294967296").size() > 0);
}

TEST(bigint_test, cout) {
    std::cout << BigInt("4294967296") << std::endl;
}

