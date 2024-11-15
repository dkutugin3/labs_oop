#include <gtest/gtest.h>
#include "../src/Money.cpp"

TEST(Init, InitStr) {
    std::string str = "123";
    Money m(str);
    std::ostringstream os;
    m.print(os);
    EXPECT_EQ(os.str(), "1.23\n");
}

TEST(Init, InitInitializerList) {
    Money m({ '1', '2', '3' });
    std::ostringstream os;
    m.print(os);
    EXPECT_EQ(os.str(), "1.23\n");
}

TEST(Init, InitSizeChar) {
    Money m(3, '5');
    std::ostringstream os;
    m.print(os);
    EXPECT_EQ(os.str(), "5.55\n");
}

TEST(Init, InitDefault) {
    Money m{};
    std::ostringstream os;
    m.print(os);
    EXPECT_EQ(os.str(), "0\n");
}

TEST(Operator, Equality) {
    Money m1("123");
    Money m2("123");
    EXPECT_TRUE(m1 == m2);
    
    Money m3("124");
    EXPECT_FALSE(m1 == m3);
}

TEST(Operator, NotEqual) {
    Money m1("123");
    Money m2("124");
    EXPECT_TRUE(m1 != m2);
    
    Money m3("123");
    EXPECT_FALSE(m1 != m3);
}

TEST(Operator, LessThan) {
    Money m1("3");
    Money m2("124");
    EXPECT_TRUE(m1 < m2);

    Money m3("2");
    EXPECT_FALSE(m1 < m3);
}

TEST(Operator, GreaterThan) {
    Money m1("123");
    Money m2("122");
    EXPECT_TRUE(m1 > m2);
    
    Money m3("124");
    EXPECT_FALSE(m1 > m3);
}

TEST(Operator, PlusEqual) {
    Money m1("153");
    Money m2("456");
    m1 += m2;
    
    std::ostringstream os;
    m1.print(os);
    EXPECT_EQ(os.str(), "6.09\n");
}

TEST(Operator, MinusEqual) {
    Money m1("456");
    Money m2("163");
    m1 -= m2;
    
    std::ostringstream os;
    m1.print(os);
    EXPECT_EQ(os.str(), "2.93\n");
}

TEST(CopyConstructor, Copy) {
    Money m1("123");
    Money m2(m1);
    
    std::ostringstream os;
    m2.print(os);
    EXPECT_EQ(os.str(), "1.23\n");
}

TEST(MoveConstructor, Move) {
    Money m1("123");
    Money m2(std::move(m1));
    
    std::ostringstream os;
    m2.print(os);
    EXPECT_EQ(os.str(), "1.23\n");
    std::ostringstream os1;
    m1.print(os1);
    EXPECT_EQ(os1.str(), "0\n");
}

TEST(Operator, Assignment) {
    Money m1("123");
    Money m2("456");
    m2 = m1;
    
    std::ostringstream os;
    m2.print(os);
    EXPECT_EQ(os.str(), "1.23\n");
}

TEST(Init, InvalidChar) {
    EXPECT_THROW(Money m("12a"), std::invalid_argument);
}

TEST(Init, InvalidList) {
    EXPECT_THROW(Money m({ '1', '2', 'a' }), std::invalid_argument);
}

TEST(Operator, SubtractInvalidSize) {
    Money m1("123");
    Money m2("1234");
    EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(Init, InvalidCharInSizeConstructor) {
    EXPECT_THROW(Money m(3, 'a'), std::invalid_argument);
}