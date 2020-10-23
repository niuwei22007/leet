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
namespace combinesum {
class Solution {
    vector<vector<int>> result_;
    vector<int> candidates_;
    vector<int> combine_;
    int tmp_;
public:
    void DFS(int target, int candIndex) {
        if (target == 0) {
            this->result_.push_back(this->combine_);
            return;
        }
        if (target < 0) {
            return;
        }
        if (candIndex == this->candidates_.size()) {
            return;
        }

        // skip
        DFS(target, candIndex + 1);

        this->tmp_ = target - this->candidates_[candIndex];
        if (this->tmp_ >= 0) {
            // current
            combine_.push_back(this->candidates_[candIndex]);
            DFS(this->tmp_, candIndex);
            combine_.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        this->candidates_ = candidates;
        sort(this->candidates_.begin(), this->candidates_.end());
        DFS(target, 0);
        return this->result_;
    }
};
}

void TestForCombineNum() {
    auto *obj = new combinesum::Solution();
    vector<int> can{2, 3, 6, 7, 11, 17, 19, 33};
    auto result = obj->combinationSum(can, 40);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
