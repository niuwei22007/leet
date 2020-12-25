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
namespace length_of_lis2 {
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        vector<int> dp(nums.size(), 1);
        vector<int> counter(nums.size(), 1);

        int maxLen = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        counter[i] = counter[j];
                    } else if (dp[j] + 1 == dp[i]){
                        counter[i] += counter[j];
                    }
                }
            }
            maxLen = max(maxLen, dp[i]);
        }


        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (dp[i] == maxLen) {
                res += counter[i];
            }
        }
        return res;
    }
};
}

void TestForMaxLengthSubSeq2() {
    auto* obj = new length_of_lis2::Solution();
    vector<int> dict{1, 2, 4, 3, 5, 4, 7, 2};

    auto res = obj->findNumberOfLIS(dict);
    printf("%d\n", res);
}
