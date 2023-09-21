#include <iostream>
#include <cassert>
#include "interval_map.h"

int main() {
    interval_map<int, char> map('A');
    map.assign(1, 20, 'd');
    map.assign(1, 19, 'P');
    map.assign(20, 22, 'P');
    map.assign(19, 29, 'P');


    map.assign(1, 5, 'B');
    assert(map[0] == 'A');
    assert(map[1] == 'B');
    assert(map[2] == 'B');
    assert(map[3] == 'B');
    assert(map[4] == 'B');
    assert(map[5] == 'A');

    map.assign(3, 8, 'C');
    assert(map[0] == 'A');
    assert(map[1] == 'B');
    assert(map[2] == 'B');
    assert(map[3] == 'C');
    assert(map[4] == 'C');
    assert(map[5] == 'C');
    assert(map[6] == 'C');
    assert(map[7] == 'C');
    assert(map[8] == 'A');
    assert(map[9] == 'A');

    map.assign(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 20, 'B');
    assert(map[std::numeric_limits<int>::min()+3] == 'B');
    assert(map[std::numeric_limits<int>::min() + 30] == 'A');

    map.assign(std::numeric_limits<int>::max() - 10, std::numeric_limits<int>::max(), 'F');
    assert(map[std::numeric_limits<int>::max() - 4 == 'F']);
    assert(map[std::numeric_limits<int>::max() - 30] == 'A');

    map.assign(2, 5, 'D');
    assert(map[0] == 'A');
    assert(map[1] == 'B');
    assert(map[2] == 'D');
    assert(map[3] == 'D');
    assert(map[4] == 'D');
    assert(map[5] == 'C');

    std::cout << "All tests passed!" << std::endl;

    return 0;
}