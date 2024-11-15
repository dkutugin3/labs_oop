#include <gtest/gtest.h>
#include "../src/function.cpp"

TEST(RemoveVowelsFunctionTest, RemovesVowelsFromSentence) {
    EXPECT_EQ(removeVowels("This website is for losers LOL!"),
              "Ths wbst s fr lsrs LL!");
}

TEST(RemoveVowelsFunctionTest, NoVowelsInString) {
    EXPECT_EQ(removeVowels("Ths wll nt chnge"), "Ths wll nt chng");
}

TEST(RemoveVowelsFunctionTest, OnlyVowelsInString) {
    EXPECT_EQ(removeVowels("aeiouAEIOU"), "");
}
TEST(RemoveVowelsFunctionTest, EmptyString) {
    EXPECT_EQ(removeVowels(""), "");
}
TEST(RemoveVowelsFunctionTest, SingleConsonant) {
    EXPECT_EQ(removeVowels("b"), "b");
}

TEST(RemoveVowelsFunctionTest, SingleVowel) {
    EXPECT_EQ(removeVowels("a"), "");
}

TEST(RemoveVowelsFunctionTest, MixedCaseInput) {
    EXPECT_EQ(removeVowels("AbCdEfGh"), "bCdfGh");
}
