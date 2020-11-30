#include "../trust.h"
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
public:
    int count = 0;

    void Backtracking(int cur, int target) {
        if (cur >= target) {
            if (cur == target) {
                count++;
            }
            return;
        }
        Backtracking(cur + 1, target);
        Backtracking(cur + 2, target);
    }

    int climbStairs(int n) {
        Backtracking(0, n);
        return count;
    }
};
}

void TestForClimbStaires() {
    auto* obj = new climb_stairs::Solution();
    auto res = obj->climbStairs(4);
    printf("%d\n", res);
}
