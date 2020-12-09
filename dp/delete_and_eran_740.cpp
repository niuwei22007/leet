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
namespace delete_earn {
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        int n = nums.size();
        array<int, 10000> label = {0};
        for (int i = 0; i < n; i++) {
            label[nums[i]] += nums[i];
        }
        array<int, 10000> dp = {0};
        dp[0] = label[0];
        dp[1] = max(label[0], label[1]);
        for (int i = 2; i < 10000; i++) {
            dp[i] = max(label[i] + dp[i - 2], dp[i - 1]);
        }
        return dp[9999];
    }
};
}

void TestForDeleteAndEarn() {
    auto* obj = new delete_earn::Solution();
    vector<int> cost{1, 2};
    auto res = obj->deleteAndEarn(cost);
    printf("%d\n", res);
}
