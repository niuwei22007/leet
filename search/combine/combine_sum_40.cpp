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
namespace combinesum2 {
class Solution {
    vector<vector<int>> result_;
    vector<int> candidates_;
    vector<int> combine_;
public:
    void DFS(int target, int candIndex) {
        if (target == 0) {
            this->result_.push_back(this->combine_);
            return;
        }
        if (target < 0) {
            return;
        }
        for (int i = candIndex; i < this->candidates_.size(); i++) {
            if ((i - 1) >= candIndex && this->candidates_[i - 1] == this->candidates_[i]) {
                continue;
            }
            if (target >= this->candidates_[i]) {
                combine_.push_back(this->candidates_[i]);
                DFS(target - this->candidates_[i], i + 1);
                combine_.pop_back();
            }
        }

    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        this->candidates_ = candidates;
        sort(this->candidates_.begin(), this->candidates_.end());
        DFS(target, 0);
        return this->result_;
    }
};
}

void TestForCombineNum2() {
    auto *obj = new combinesum2::Solution();
    vector<int> can{10, 1, 2, 7, 6, 1, 5};
//    vector<int> can{7, 33};
    auto result = obj->combinationSum2(can, 8);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
