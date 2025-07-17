#include <gtest/gtest.h>
#include "color.hpp"

// Demonstrate some basic assertions.
TEST(WriteColorTest, OutputsCorrectValues)
{
    std::ostringstream oss;
    auto red = color(1.0, 0.0, 0.0);

    write_color(oss, red);
    EXPECT_EQ(oss.str(), "255 0 0\n");
}

TEST(WriteColorTest, ClampsValuesAboveOne)
{
    std::ostringstream oss;
    write_color(oss, color(1.5, 2.0, 0.0));
    EXPECT_EQ(oss.str(), "255 255 0\n");
}

TEST(WriteColorTest, ClampsValuesBelowZero)
{
    std::ostringstream oss;
    write_color(oss, color(-1.0, 0.0, -0.5));
    EXPECT_EQ(oss.str(), "0 0 0\n");
}

TEST(WriteColorTest, RoundsUpToNearestInt)
{
    std::ostringstream oss;
    write_color(oss, color(0.5, 0.5, 0.5));
    EXPECT_EQ(oss.str(), "128 128 128\n");
}