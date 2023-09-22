#include <iostream>
#include <cassert>
#include "interval_map.h"

void main() {
    interval_map<int, char> map('A');
    map.assign(1, 20, 'd');
    assert(map[0] == 'A'); // 0 => 'A'
    assert(map[1] == 'd'); // 1-20 => 'd'
    assert(map[21] == 'A'); // 21 => 'A'

    map.assign(1, 19, 'P');
    assert(map[0] == 'A'); // 0 => 'A'
    assert(map[1] == 'P'); // 1 => 'P'
    assert(map[2] == 'P'); // 2 => 'P'
    assert(map[20] == 'A'); // 20 => 'A'
    assert(map[21] == 'A'); // 21 => 'A'

    map.assign(20, 22, 'P');
    assert(map[19] == 'd'); // 19 => 'd'
    assert(map[20] == 'P'); // 20-22 => 'P'
    assert(map[23] == 'A'); // 23 => 'A'

    map.assign(19, 29, 'P');
    assert(map[18] == 'P'); // 18 => 'P'
    assert(map[19] == 'P'); // 19 => 'P'
    assert(map[20] == 'P'); // 20-22 => 'P'
    assert(map[29] == 'A'); // 29 => 'A'
    assert(map[30] == 'A'); // 30 => 'A'

    map.assign(1, 5, 'B');
    assert(map[0] == 'A'); // 0 => 'A'
    assert(map[1] == 'B'); // 1-5 => 'B'
    assert(map[6] == 'P'); // 6-19 => 'P'
    assert(map[20] == 'P'); // 20-22 => 'P'
    assert(map[29] == 'A'); // 29 => 'A'

    map.assign(3, 8, 'C');
    assert(map[0] == 'A'); // 0 => 'A'
    assert(map[1] == 'B'); // 1-2 => 'B'
    assert(map[3] == 'C'); // 3-8 => 'C'
    assert(map[8] == 'P'); // 3-7 => 'P'

    map.assign(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 20, 'B');
    assert(map[std::numeric_limits<int>::min() - 1] == 'A'); // Below minimum bound
    assert(map[std::numeric_limits<int>::min()] == 'B'); // Min to Min+19 => 'B'
    assert(map[std::numeric_limits<int>::min() + 20] == 'A'); // Above the assigned range

    map.assign(std::numeric_limits<int>::max() - 10, std::numeric_limits<int>::max(), 'F');
    assert(map[std::numeric_limits<int>::max() - 11] == 'A'); // Below the assigned range
    assert(map[std::numeric_limits<int>::max() - 10] == 'F'); // Max-10 to Max => 'F'
    assert(map[std::numeric_limits<int>::max()] == 'A'); // Above maximum bound

    map.assign(2, 5, 'D');
    assert(map[1] == 'B'); // 1 => 'B'
    assert(map[2] == 'D'); // 2-5 => 'D'
    assert(map[6] == 'C'); 

    std::cout << "All tests passed!" << std::endl;
    return ;
}
