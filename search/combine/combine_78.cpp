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
namespace combine78 {
class Solution {
    vector<vector<int>> result_;
    vector<int> nums_;
    vector<int> combine_;
public:
    void DFS(int candIndex, int totalLen, int targetLen) {
        if (combine_.size() == targetLen) {
            result_.push_back(combine_);
            return;
        }
        for (int i = candIndex; i < totalLen; i++) {
            combine_.push_back(nums_[i]);
            DFS(i + 1, totalLen, targetLen);
            combine_.pop_back();
        }
    }

    void combine(int totalLen, int targetLen) {
        if (targetLen == totalLen) {
            vector<int> tmp(targetLen, 0);
            for (int i = 0; i < targetLen; i++) {
                tmp[i] = nums_[i];
            }
            result_.push_back(tmp);
            return;
        }
        DFS(0, totalLen, targetLen);
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        result_.emplace_back();
        if (nums.empty()) {
            return result_;
        }
        nums_ = nums;
        sort(nums_.begin(), nums_.end());
        size_t size = (size_t) 1 << nums_.size();
        result_.reserve(size);
        int totalLen = nums_.size();
        for (int i = 1; i <= totalLen; i++) {
            combine(nums_.size(), i);
        }
        return result_;
    }

    vector<vector<int>> subsets2(vector<int> &nums) {
        //子集的长度是2的nums.length次方，这里通过移位计算
        int length = (int) 1 << nums.size();
        vector<vector<int>> res(length);
        //遍历从0到length中间的所有数字，根据数字中1的位置来找子集
        for (int i = 0; i < length; i++) {
            vector<int> list;
            for (int j = 0; j < nums.size(); j++) {
                //如果数字i的某一个位置是1，就把数组中对
                //应的数字添加到集合
                printf("i=%d(%x), j=%d(%x), i>>j=%d, &1=%d\n", i, i, j, j, i >> j, (i >> j) & 1);
                if (((i >> j) & 1) == 1) {
                    list.push_back(nums[j]);
                }
            }
            res.push_back(list);
        }
        return res;
    }
};
}

void TestForCombine78() {
    auto *obj = new combine78::Solution();
    vector<int> nums{1, 2, 3};
    auto result = obj->subsets(nums);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }

    auto result2 = obj->subsets2(nums);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
