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
namespace max_sub_seq {
class Solution {
public:
    int maxSubArray_DP(vector<int>& nums) {
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

    struct Node {
        int iSum, lSum, rSum, mSum;
    };

    Node Combine(Node& left, Node& right) {
        Node n;
        n.iSum = left.iSum + right.iSum;
        n.lSum = max(left.lSum, left.iSum + right.lSum);
        n.rSum = max(left.rSum + right.iSum, right.rSum);
        n.mSum = max(max(left.mSum, right.mSum), left.rSum + right.lSum);
        return n;
    }

    Node Get(vector<int>& nums, int l, int r) {
        if (l == r) {
            return {nums[l], nums[l], nums[l], nums[l]};
        }
        int mid = (l + r) >> 1;
        Node left = Get(nums, l, mid);
        Node right = Get(nums, mid + 1, r);
        return Combine(left, right);
    }

    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        Node n = Get(nums, 0, nums.size() - 1);
        return n.mSum;
    }
};
}

void TestForMaxSubSeq() {
    auto* obj = new max_sub_seq::Solution();
    vector<int> cost{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto res = obj->maxSubArray(cost);
    printf("%d\n", res);
}
