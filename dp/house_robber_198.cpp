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
namespace house_robber {
class Solution {
public:
    void DFS(vector<int>& nums, int index, int& maxVal, int cur) {
        if (index >= nums.size()) {
            if (cur > maxVal) {
                maxVal = cur;
            }
            return;
        }
        DFS(nums, index + 2, maxVal, cur + nums[index]);
        DFS(nums, index + 3, maxVal, cur + nums[index]);
    }

    int rob_DFS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        int maxVal = 0;
        DFS(nums, 0, maxVal, 0);
        DFS(nums, 1, maxVal, 0);
        return maxVal;
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
        int len = nums.size();
        vector<int> dp(len, 0);
        dp[len - 1] = nums[len - 1];
        dp[len - 2] = nums[len - 2];
        for (int i = len - 3; i >= 0; i--) {
            if (i + 3 < len) {
                dp[i] = nums[i] + max(dp[i + 2], dp[i + 3]);
            } else if (i + 2 < len) {
                dp[i] = nums[i] + dp[i + 2];
            }
        }
        return max(dp[0], dp[1]);
    }
};
}

void TestForHouseRobber() {
    auto* obj = new house_robber::Solution();
    vector<int> cost{226, 174, 214, 16, 218, 48, 153, 131, 128, 17, 157, 142, 88, 43, 37, 157, 43, 221, 191, 68, 206,
                     23, 225, 82, 54, 118, 111, 46, 80, 49, 245, 63, 25, 194, 72, 80, 143, 55, 209, 18, 55, 122, 65, 66,
                     177, 101, 63, 201, 172, 130, 103, 225, 142, 46, 86, 185, 62, 138, 212, 192, 125, 77, 223, 188, 99,
                     228, 90, 25, 193, 211, 84, 239, 119, 234, 85, 83, 123, 120, 131, 203, 219, 10, 82, 35, 120, 180,
                     249, 106, 37, 169, 225, 54, 103, 55, 166, 124};
    auto res = obj->rob(cost);
    printf("%d\n", res);
}
