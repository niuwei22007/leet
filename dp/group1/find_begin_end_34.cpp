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

using namespace std;
namespace find_begin_end {
class Solution {
public:
    int BinarySearch(vector<int>& nums, int target, bool isLeft) {
        if (nums.empty()) {
            return -1;
        }
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        int ans = nums.size();
        while (left <= right) {
            mid = (left + right) >> 1;
            if (nums[mid] > target || (isLeft && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty() || nums[0] > target || nums[nums.size() - 1] < target) {
            return {-1, -1};
        }
        int b = BinarySearch(nums, target, true);
        int e = BinarySearch(nums, target, false) - 1;
        if (b <= e && e < nums.size() && nums[b] == target && nums[e] == target) {
            return {b, e};
        }
        return {-1, -1};
    }
};
}

void TestForFindBeginEnd() {
    vector<int> cost{1, 2, 3};
    auto* obj = new find_begin_end::Solution();
    auto res = obj->searchRange(cost, 1);
    printf("%d, %d\n", res[0], res[1]);
}
