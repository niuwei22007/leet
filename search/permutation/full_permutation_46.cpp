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
namespace permutation {
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
            if (labels[i]) {
                continue;
            }
            combine_.push_back(nums[i]);
            labels[i] = true;
            DFS(length, nums, labels);
            combine_.pop_back();
            labels[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        vector<bool> labels(nums.size(), false);
        size_t size = 1;
        for (int i = 2; i < nums.size(); ++i) {
            size *= i;
        }
        result_.reserve(size);
        DFS(nums.size(), nums, labels);
        return result_;
    }
};
}

void TestForPermutation() {
    auto *obj = new permutation::Solution();
    vector<int> nums{3, 8, 9};
    auto result = obj->permute(nums);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
