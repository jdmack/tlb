
#include <gtest/gtest.h>
#include "point.h"

TEST(Point,Basic)
{
    Point point();
    EXPECT_EQ (point.x(), 0);
    EXPECT_EQ (point.y(), 0);
}

