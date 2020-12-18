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
#include <stack>

using namespace std;
namespace length_of_lis {
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
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
};
}

void TestForMaxLengthSubSeq() {
    auto* obj = new length_of_lis::Solution();
    vector<int> dict{1, 3, 6, 7, 9, 4, 10, 5, 6};

    auto res = obj->lengthOfLIS(dict);
    printf("%d\n", res);
}
