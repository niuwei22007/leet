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
namespace subset2 {
class Solution {
    vector<vector<int>> result_;
    vector<int> combine_;
public:
    void DFS(int start, int end, vector<int> &nums) {
        result_.push_back(combine_);
        for (int i = start; i < end; i++) {
            if (i - 1 >= start && nums[i] == nums[i - 1]) {
                continue;
            }
            combine_.push_back(nums[i]);
            DFS(i + 1, end, nums);
            combine_.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        DFS(0, nums.size(), nums);
        return result_;
    }
};
}

void TestForSubset2() {
    auto *obj = new subset2::Solution();
    vector<int> nums{2, 1, 2};
    auto result = obj->subsetsWithDup(nums);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
