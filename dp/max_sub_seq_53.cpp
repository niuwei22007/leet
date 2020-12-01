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
namespace max_sub_seq {
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int maxVal = nums[0];
        int preMax = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            preMax = max(preMax + nums[i], nums[i]);
            maxVal = max(preMax, maxVal);
        }
        return maxVal;
    }
};
}

void TestForMaxSubSeq() {
    auto* obj = new max_sub_seq::Solution();
    vector<int> cost{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto res = obj->maxSubArray(cost);
    printf("%d\n", res);
}
