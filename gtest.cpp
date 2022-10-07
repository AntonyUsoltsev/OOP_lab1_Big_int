#include <iostream>
#include "gtest/gtest.h"
#include "BigInt.h"

TEST(bigint_test_costructor, int_constructor) {
    EXPECT_EQ("0", (std::string) BigInt(0));
    EXPECT_EQ("123456789", (std::string) BigInt(123456789));
    EXPECT_EQ("0", (std::string) BigInt(-0));
    EXPECT_EQ("2147483647", (std::string) BigInt(2147483647));
    EXPECT_EQ("-2147483648", (std::string) BigInt(-2147483648));
}

TEST(bigint_test_costructor, str_constructor) {
    EXPECT_EQ("0", (std::string) BigInt("0"));
    EXPECT_EQ("0", (std::string) BigInt("-0"));
    EXPECT_EQ("1234567899876543210", (std::string) BigInt("1234567899876543210"));
    EXPECT_EQ("123456789", (std::string) BigInt("000000000123456789"));
    EXPECT_EQ("-1239876545151515", (std::string) BigInt("-1239876545151515"));
}

TEST(bigint_test_costructor, copy_constructor) {
    BigInt val1 = BigInt(123456789);
    const BigInt &val2 = val1;
    EXPECT_EQ("123456789", (std::string) val2);
}

TEST(bigint_test_operator, copy_operator) {
    BigInt val1 = BigInt(123456789);
    val1 = val1;
    EXPECT_EQ("123456789", (std::string) val1);
}

TEST(bigint_test_operator, bitwise_not) {
    BigInt val1 = BigInt(123456789);
    EXPECT_EQ("-123456790", (std::string) ~val1);
}

TEST(bigint_test_operator, postfix_unary_increment) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = val1++;
    EXPECT_EQ(1001, int(val1));
    EXPECT_EQ(1000, int(val2));
}

TEST(bigint_test_operator, prefix_unary_increment) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = ++val1;
    EXPECT_EQ(1001, int(val1));
    EXPECT_EQ(1001, int(val2));
}

TEST(bigint_test_operator, postfix_unary_decrement) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = val1--;
    EXPECT_EQ(999, int(val1));
    EXPECT_EQ(1000, int(val2));
}

TEST(bigint_test_operator, prefix_unary_decrement) {
    BigInt val1 = BigInt(1000);
    const BigInt val2 = --val1;
    EXPECT_EQ(999, int(val1));
    EXPECT_EQ(999, int(val2));
}

TEST(bigint_test_operator, plus_assign_1) {
    BigInt val1 = BigInt(1000);
    BigInt val2 = BigInt(150);
    val1 += val2;
    EXPECT_EQ(1150, int(val1));
    EXPECT_EQ(150, int(val2));
}

TEST(bigint_test_operator, plus_assign_2) {
    BigInt val1 = BigInt(1000);
    BigInt val2 = BigInt(-150);
    val1 += val2;
    EXPECT_EQ(850, int(val1));
    EXPECT_EQ(-150, int(val2));
}

TEST(bigint_test_operator, plus_assign_3) {
    BigInt val1 = BigInt(-1000);
    BigInt val2 = BigInt(600);
    val1 += val2;
    EXPECT_EQ(-400, int(val1));
    EXPECT_EQ(600, int(val2));
}

TEST(bigint_test_operator, plus_assign_4) {
    BigInt val1 = BigInt(-1000);
    BigInt val2 = BigInt(-600);
    val1 += val2;
    EXPECT_EQ(-1600, int(val1));
    EXPECT_EQ(-600, int(val2));
}

TEST(bigint_test_operator, plus_assign_5) {
    BigInt val1 = BigInt(-1000);
    BigInt val2 = BigInt("123456789987654321");
    val1 += val2;
    EXPECT_EQ("123456789987653321", (std::string) val1);
    EXPECT_EQ("123456789987654321", (std::string) val2);
}

TEST(bigint_test_operator, minus_assign_1) {
    BigInt val1 = BigInt(1000);
    BigInt val2 = BigInt(150);
    val1 -= val2;
    EXPECT_EQ(850, int(val1));
    EXPECT_EQ(150, int(val2));
}

TEST(bigint_test_operator, minus_assign_2) {
    BigInt val1 = BigInt(1000);
    BigInt val2 = BigInt(-150);
    val1 -= val2;
    EXPECT_EQ(1150, int(val1));
    EXPECT_EQ(-150, int(val2));
}

TEST(bigint_test_operator, minus_assign_3) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("12345625198495948519");
    val1 -= val2;
    EXPECT_EQ(0, int(val1));
    EXPECT_EQ("12345625198495948519", (std::string) val2);
}

TEST(bigint_test_operator, minus_assign_4) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt(0);
    val1 -= val2;
    EXPECT_EQ("12345625198495948519", (std::string) val1);
    EXPECT_EQ(0, int(val2));
}

TEST(bigint_test_operator, mult_assign_1) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt(0);
    val1 *= val2;
    EXPECT_EQ(0, int(val1));
    EXPECT_EQ(0, int(val2));

}

TEST(bigint_test_operator, mult_assign_2) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("1111111111");
    val1 *= val2;
    EXPECT_EQ("13717361330290428887944894609", (std::string) val1);
    EXPECT_EQ("1111111111", (std::string) val2);
}

TEST(bigint_test_operator, mult_assign_3) {
    BigInt val1 = BigInt("-12345625198495948519");
    BigInt val2 = BigInt("1111111111");
    val1 *= val2;
    EXPECT_EQ("-13717361330290428887944894609", (std::string) val1);
    EXPECT_EQ("1111111111", (std::string) val2);
}

TEST(bigint_test_operator, div_assign_1) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("1111111111");
    val1 /= val2;
    EXPECT_EQ("11111062679", (std::string) val1);
    EXPECT_EQ("1111111111", (std::string) val2);
}

TEST(bigint_test_operator, div_assign_2) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("1");
    val1 /= val2;
    EXPECT_EQ("12345625198495948519", (std::string) val1);
    EXPECT_EQ("1", (std::string) val2);
}

TEST(bigint_test_operator, div_assign_3) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("-11559198119818498151984849815198");
    val1 /= val2;
    EXPECT_EQ("0", (std::string) val1);
    EXPECT_EQ("-11559198119818498151984849815198", (std::string) val2);
}

TEST(bigint_test_operator, mod_assign_1) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("112345");
    val1 %= val2;
    EXPECT_EQ("21239", (std::string) val1);
    EXPECT_EQ("112345", (std::string) val2);
}

TEST(bigint_test_operator, mod_assign_2) {
    BigInt val1 = BigInt("12345625198495948519");
    BigInt val2 = BigInt("-112345");
    val1 %= val2;
    EXPECT_EQ("21239", (std::string) val1);
    EXPECT_EQ("-112345", (std::string) val2);
}

TEST(bigint_test_operator, mod_assign_3) {
    BigInt val1 = BigInt("-10000");
    BigInt val2 = BigInt("-10");
    val1 %= val2;
    EXPECT_EQ("0", (std::string) val1);
    EXPECT_EQ("-10", (std::string) val2);
}

TEST(bigint_test_operator, xor_assign) {
    BigInt val1 = BigInt("1488");
    BigInt val2 = BigInt("18919");
    val1 ^= val2;
    EXPECT_EQ("19511", (std::string) val1);
    EXPECT_EQ("18919", (std::string) val2);
}

TEST(bigint_test_operator, and_assign) {
    BigInt val1 = BigInt("1488");
    BigInt val2 = BigInt("18919");
    val1 &= val2;
    EXPECT_EQ("448", (std::string) val1);
    EXPECT_EQ("18919", (std::string) val2);
}

TEST(bigint_test_operator, or_assign) {
    BigInt val1 = BigInt("1488");
    BigInt val2 = BigInt("18919");
    val1 |= val2;
    EXPECT_EQ("19959", (std::string) val1);
    EXPECT_EQ("18919", (std::string) val2);
}

TEST(bigint_test_operator, unary_plus) {
    BigInt val1("4511651651651");
    EXPECT_EQ("4511651651651", (std::string) +val1);

    BigInt val2("-4511651651651");
    EXPECT_EQ("-4511651651651", (std::string) +val2);
}

TEST(bigint_test_operator, unary_minus) {
    BigInt val1("4511651651651");
    EXPECT_EQ("-4511651651651", (std::string) -val1);

    BigInt val2("-4511651651651");
    EXPECT_EQ("4511651651651", (std::string) -val2);
}

TEST(bigint_test_operator, compare_test) {
    EXPECT_TRUE(BigInt("0") == BigInt("-0"));
    EXPECT_TRUE(BigInt("123456789987") == BigInt("123456789987"));

    EXPECT_TRUE(BigInt("123456789987") != BigInt("984984295"));
    EXPECT_TRUE(BigInt("123456789987") != BigInt("-123456789987"));

    EXPECT_TRUE(BigInt("147149498419419") > BigInt("5"));
    EXPECT_TRUE(BigInt("4294967296") > BigInt("-94984984984894"));
    EXPECT_TRUE(BigInt("-49848494") > BigInt("-49848496"));

    EXPECT_TRUE(BigInt("1") < BigInt("429499849484"));
    EXPECT_TRUE(BigInt("-1949232149") < BigInt("135"));
    EXPECT_TRUE(BigInt("-1984984156") < BigInt("-1984984152"));

    EXPECT_TRUE(BigInt("16516165") <= BigInt("16516165"));
    EXPECT_TRUE(BigInt("16516165") >= BigInt("16516165"));
}

TEST(bigint_test_operator, size) {
    EXPECT_TRUE(BigInt("9898451165").size() == 3);
}

TEST(bigint_test_operator, cout) {
    std::cout << BigInt("49845112123") << std::endl;
}

TEST(bigint_test_operator, operators) {
    EXPECT_EQ("3485960683212", (std::string) (BigInt("1919841516") + BigInt("3484040841696")));
    EXPECT_EQ("-3482121000180", (std::string) (BigInt("1919841516") - BigInt("3484040841696")));
    EXPECT_EQ("6688806251327564651136", (std::string) (BigInt("1919841516") * BigInt("3484040841696")));
    EXPECT_EQ("0", (std::string) (BigInt("1919841516") / BigInt("3484040841696")));
    EXPECT_EQ("3484349512972", (std::string) (BigInt("1919841516") ^ BigInt("3484040841696")));
    EXPECT_EQ("1919841516", (std::string) (BigInt("1919841516") % BigInt("3484040841696")));
    EXPECT_EQ("805585120", (std::string) (BigInt("1919841516") & BigInt("3484040841696")));
    EXPECT_EQ("3485155098092", (std::string) (BigInt("1919841516") | BigInt("3484040841696")));
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}