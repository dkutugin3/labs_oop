#include <gtest/gtest.h>
#include "../include/figure.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"
#include "../include/pentagon.hpp"

TEST(FigureTest, PentagonTest) {
    Pentagon pentagon;
    std::istringstream input("0 0 2 0 3 1 1 3 -1 1");
    input >> pentagon;

    EXPECT_DOUBLE_EQ(static_cast<double>(pentagon), 7.0);

    auto center = pentagon.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(FigureTest, HexagonTest) {
    Hexagon hexagon;
    std::istringstream input("0 0 2 0 3 2 2 4 0 4 -1 2");
    input >> hexagon;

    EXPECT_DOUBLE_EQ(static_cast<double>(hexagon), 8.0);

    auto center = hexagon.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(FigureTest, OctagonTest) {
    Octagon octagon;
    std::istringstream input("0 0 2 0 3 1 3 3 2 4 0 4 -1 3 -1 1");
    input >> octagon;

    EXPECT_DOUBLE_EQ(static_cast<double>(octagon), 5.0);

    auto center = octagon.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(FigureTest, ComparisonOperators) {
    Pentagon pentagon1;
    Pentagon pentagon2;
    std::istringstream input1("0 0 2 0 3 1 1 3 -1 1");
    std::istringstream input2("0 0 2 0 3 1 1 3 -1 1");

    input1 >> pentagon1;
    input2 >> pentagon2;

    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(FigureTest, AssignmentOperators) {
    Hexagon hex1;
    std::istringstream input("0 0 2 0 3 2 2 4 0 4 -1 2");
    input >> hex1;

    Hexagon hex2;
    hex2 = hex1;

    EXPECT_TRUE(hex1 == hex2);

    Hexagon hex3;
    hex3 = std::move(hex1);

    EXPECT_TRUE(hex3 == hex2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
