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
        auto bit = lower_bound(nums.begin(), nums.end(), target);
        if (bit == nums.end() || *bit != target) {
            return {-1, -1};
        }
        int begin = bit - nums.begin();
        auto eit = upper_bound(bit, nums.end(), target);
        if (eit == nums.end()) {
            return {begin, (int)nums.size() - 1};
        }
        int end = (eit - nums.begin()) - 1;
        return {begin, end};
    }
};
}

void TestForFindBeginEnd() {
    vector<int> cost{5, 7, 7, 8, 8, 10};
    auto* obj = new find_begin_end::Solution();
    auto res = obj->searchRange(cost, 8);
    printf("%d, %d\n", res[0], res[1]);
}
