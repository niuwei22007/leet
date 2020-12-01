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
        auto[b, e] = equal_range(nums.begin(), nums.end(), target);
        if (b == e) {
            return {-1, -1};
        }
        return {(int)distance(nums.begin(), b), (int)distance(nums.begin(), e) - 1};
    }
};
}

void TestForFindBeginEnd() {
    vector<int> cost{5, 7, 7, 8, 8, 10};
    auto* obj = new find_begin_end::Solution();
    auto res = obj->searchRange(cost, 8);
    printf("%d, %d\n", res[0], res[1]);
}
