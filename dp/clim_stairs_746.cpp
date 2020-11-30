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
namespace climb_stairs2 {
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() < 3) {
            return *min_element(cost.begin(), cost.end());
        }
        int len = cost.size();
        int right = cost[len - 1];
        int left = cost[len - 2];
        int temp;
        for (int i = len - 3; i >= 0; i--) {
            temp = min(cost[i] + left, cost[i] + right);
            right = left;
            left = temp;
        }
        return min(left, right);
    }
};
}

void TestForClimbStaires2() {
    auto* obj = new climb_stairs2::Solution();
    vector<int> cost{1, 2};
    auto res = obj->minCostClimbingStairs(cost);
    printf("%d\n", res);
}
