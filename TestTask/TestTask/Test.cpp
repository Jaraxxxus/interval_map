#include <gtest/gtest.h>
#include "interval_map.h"

TEST(IntervalMapTest, IntervalsWithSameValue) {
    interval_map<int, char> map('A');
    map.assign(1, 20, 'A');
    map.assign(3, 14, 'A');
    map.assign(std::numeric_limits<int>::min(), 7, 'A');
    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map[0], 'A'); // 0 => 'A'
    EXPECT_EQ(map[1], 'A'); // 1-2 => 'A'
    EXPECT_EQ(map[15], 'A'); // 15 => 'A'
    EXPECT_EQ(map[21], 'A'); // 21 => 'A'

    map.assign(700, 720, 'G');
    map.assign(703, 733, 'G');
    map.assign(670, 705, 'G');
    EXPECT_EQ(map[670], 'G'); 
    EXPECT_EQ(map[732], 'G');
    EXPECT_EQ(map[733], 'A'); 
    EXPECT_EQ(map.size(), 4); 
}

TEST(IntervalMapTest, OverlappingAssignments) {
    interval_map<int, char> map('A');

    map.assign(1, 5, 'B');
    map.assign(3, 8, 'C');
    map.assign(2, 5, 'D');

    EXPECT_EQ(map[1], 'B'); // 1 => 'B'
    EXPECT_EQ(map[2], 'D'); // 2-5 => 'D'
    EXPECT_EQ(map[6], 'C'); // 6 => 'C'
}

TEST(IntervalMapTest, BoundaryAssignments) {
    interval_map<int, char> map('A');

    map.assign(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 20, 'B');
    EXPECT_EQ(map[std::numeric_limits<int>::min() - 1], 'A'); // Below minimum bound
    EXPECT_EQ(map[std::numeric_limits<int>::min()], 'B'); // Min to Min+19 => 'B'
    EXPECT_EQ(map[std::numeric_limits<int>::min() + 20], 'A'); // Above the assigned range

    map.assign(std::numeric_limits<int>::max() - 10, std::numeric_limits<int>::max(), 'F');
    EXPECT_EQ(map[std::numeric_limits<int>::max() - 11], 'A'); // Below the assigned range
    EXPECT_EQ(map[std::numeric_limits<int>::max() - 10], 'F'); // Max-10 to Max => 'F'
    EXPECT_EQ(map[std::numeric_limits<int>::max()], 'A'); // Above maximum bound
}

TEST(IntervalMapTest, MoreAssignments) {
    interval_map<int, char> map('A');
    map.assign(1, 20, 'd');

    map.assign(1, 19, 'P');
    EXPECT_EQ(map[0], 'A'); // 0 => 'A'
    EXPECT_EQ(map[1], 'P'); // 1 => 'P'
    EXPECT_EQ(map[2], 'P'); // 2 => 'P'
    EXPECT_EQ(map[20], 'A'); // 20 => 'A'
    EXPECT_EQ(map[21], 'A'); // 21 => 'A'

    map.assign(20, 22, 'P');
    EXPECT_EQ(map[19], 'd'); // 19 => 'd'
    EXPECT_EQ(map[20], 'P'); // 20-22 => 'P'
    EXPECT_EQ(map[23], 'A'); // 23 => 'A'

    map.assign(19, 29, 'P');
    EXPECT_EQ(map[18], 'P'); // 18 => 'P'
    EXPECT_EQ(map[19], 'P'); // 19 => 'P'
    EXPECT_EQ(map[20], 'P'); // 20-22 => 'P'
    EXPECT_EQ(map[29], 'A'); // 29 => 'A'
    EXPECT_EQ(map[30], 'A'); // 30 => 'A'

    map.assign(1, 5, 'B');
    EXPECT_EQ(map[0], 'A'); // 0 => 'A'
    EXPECT_EQ(map[1], 'B'); // 1-5 => 'B'
    EXPECT_EQ(map[6], 'P'); // 6-19 => 'P'
    EXPECT_EQ(map[20], 'P'); // 20-22 => 'P'
    EXPECT_EQ(map[29], 'A'); // 29 => 'A'

    map.assign(3, 8, 'C');
    EXPECT_EQ(map[0], 'A'); // 0 => 'A'
    EXPECT_EQ(map[1], 'B'); // 1 => 'B'
    EXPECT_EQ(map[3], 'C'); // 3-8 => 'C'
    EXPECT_EQ(map[8], 'P'); // 3-7 => 'P'

    map.assign(2, 5, 'D');
    EXPECT_EQ(map[1], 'B'); // 1 => 'B'
    EXPECT_EQ(map[2], 'D'); // 2-5 => 'D'
    EXPECT_EQ(map[6], 'C'); // 6 => 'C'
}

TEST(IntervalMapTest, belowMinimumBound) {
    interval_map<int, char> map('A');
    map.assign(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 20, 'B');

    EXPECT_EQ(map[std::numeric_limits<int>::min() - 1], 'A'); // Below minimum bound
    EXPECT_EQ(map[std::numeric_limits<int>::min()], 'B'); // Min to Min+19 => 'B'
    EXPECT_EQ(map[std::numeric_limits<int>::min() + 20], 'A'); // Above the assigned range
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
