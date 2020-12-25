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
#include <stack>

using namespace std;
namespace length_of_lis {
class Solution {
public:
    int lengthOfLIS_DP(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }

    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        dp.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > dp.back()) {
                dp.push_back(nums[i]);
            } else {
                int l = 0;
                int r = (int)dp.size() - 1;
                int mid = (l + r) / 2;
                while (l < r) {
                    if (dp[mid] >= nums[i]) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                    mid = (l + r) / 2;
                }
                dp[mid] = nums[i];
            }
        }
        return dp.size();
    }
};
}

void TestForMaxLengthSubSeq() {
    auto* obj = new length_of_lis::Solution();
    vector<int> dict{10, 9, 2, 5, 3, 7, 101, 18};

    auto res = obj->lengthOfLIS(dict);
    printf("%d\n", res);
}
