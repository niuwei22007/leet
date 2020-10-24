//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
namespace permutation2 {
class Solution {
    vector<int> combine_;
    vector<vector<int>> result_;
public:
    void DFS(int length, vector<int> &nums, vector<bool> &labels) {
        if (combine_.size() == length) {
            result_.push_back(combine_);
            return;
        }
        for (int i = 0; i < length; ++i) {
            if (labels[i] || (i >= 1 && nums[i] == nums[i - 1]) && !labels[i - 1]) {
                continue;
            }
            combine_.push_back(nums[i]);
            labels[i] = true;
            DFS(length, nums, labels);
            combine_.pop_back();
            labels[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<bool> labels(nums.size(), false);
        DFS(nums.size(), nums, labels);
        return result_;
    }
};
}

void TestForPermutation2() {
    auto *obj = new permutation2::Solution();
    vector<int> nums{4, 3, 3, 9};
    auto result = obj->permuteUnique(nums);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
