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
namespace house_robber2 {
class Solution {
public:
    int DP_press(vector<int>& nums, int start, int end) {
        int pre = 0;
        int cur = 0;
        int tmp;
        for (int i = start; i < end; i++) {
            tmp = cur;
            cur = max(cur, pre + nums[i]);
            pre = tmp;
        }
        return cur;
    }

    int DP(vector<int>& nums, int start, int end) {
        vector<int> dp(nums.size(), 0);
        dp[start] = nums[start];
        dp[start + 1] = max(dp[start], nums[start + 1]);
        for (int i = start + 2; i < end; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[end - 1];
    }

    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }

        int left = DP(nums, 0, nums.size() - 1);
        int right = DP(nums, 1, nums.size());
        printf("left:%d, right:%d\n", left, right);
        return max(left, right);
    }
};
}

void TestForHouseRobber2() {
    auto* obj = new house_robber2::Solution();
    vector<int> cost{1, 3, 1, 3, 100};
    auto res = obj->rob(cost);
    printf("%d\n", res);
}
