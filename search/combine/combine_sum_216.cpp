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
namespace combinesum3 {
class Solution {
    vector<int> combine_;
    vector<vector<int>> result_;
public:
    void DFS(int target, int start, int length) {
        if (target == 0 && combine_.size() == length) {
            result_.push_back(combine_);
            return;
        }
        if (target < 0 || combine_.size() >= length) {
            return;
        }
        for (int i = start; i < 10; ++i) {
            combine_.push_back(i);
            DFS(target - i, i + 1, length);
            combine_.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        DFS(n, 1, k);
        return result_;
    }
};
}

void TestForCombineNum3() {
    auto *obj = new combinesum3::Solution();
    auto result = obj->combinationSum3(3, 8);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
