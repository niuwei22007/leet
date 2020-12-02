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
        int maxVal = 0;
        DFS(nums, 0, maxVal, 0);
        DFS(nums, 1, maxVal, 0);
        return maxVal;
    }
};
}

void TestForHouseRobber() {
    auto* obj = new house_robber::Solution();
    vector<int> cost{2,7,9,3,1};
    auto res = obj->rob(cost);
    printf("%d\n", res);
}
