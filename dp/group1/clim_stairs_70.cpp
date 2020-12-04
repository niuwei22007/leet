#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;
namespace climb_stairs {
class Solution {
    int left = 1;
    int right = 2;
    int tmp = 0;
public:

    int climbStairs(int n) {
        if (n < 3) {
            return n;
        }
        for (int i = 2; i < n; i++) {
            tmp = left + right;
            left = right;
            right = tmp;
        }
        return right;
    }
};
}

void TestForClimbStaires() {
    auto* obj = new climb_stairs::Solution();
    auto res = obj->climbStairs(5);
    printf("%d\n", res);
}
