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
namespace find_begin_end {
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty() || nums[0] > target || nums[nums.size() - 1] < target) {
            return {-1, -1};
        }
        vector<int> targetV{target};
        auto it = find_first_of(nums.begin(), nums.end(), targetV.begin(), targetV.end());
        if (it == nums.end()) {
            return {-1, -1};
        }
        int begin = it - nums.begin();
        it = find_end(nums.begin(), nums.end(), targetV.begin(), targetV.end());
        int end = it - nums.begin();
        return {begin, end};
    }
};
}

void TestForFindBeginEnd() {
    vector<int> cost{5, 7, 7, 8, 8, 10};
    auto* obj = new find_begin_end::Solution();
    auto res = obj->searchRange(cost, 6);
    printf("%d, %d\n", res[0], res[1]);
}
