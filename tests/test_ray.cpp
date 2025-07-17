#include <gtest/gtest.h>
#include "ray.hpp"

TEST(RayTest, GetValueAtT)
{
    ray r(point3(1, 0, 0), vec3(1, 0, 0));

    auto p = r.at(2);
    EXPECT_EQ(p.x(), 3);
    EXPECT_EQ(p.y(), 0);
    EXPECT_EQ(p.z(), 0);
}