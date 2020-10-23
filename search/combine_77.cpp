//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
namespace combine77 {
class Solution {
    vector<vector<int>> result_;
    vector<int> combine_;
    int n_, k_;
public:
    void DFS(int candIndex) {
        if (combine_.size() == this->k_) {
            result_.push_back(combine_);
            return;
        }
        for (int i = candIndex; i < this->n_; i++) {
            combine_.push_back(i + 1);
            DFS(i + 1);
            combine_.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        if (n < k) {
            return this->result_;
        }
        if (n == k) {
            vector<int> tmp(n, 0);
            for (int i = 0; i < n; i++) {
                tmp[i] = i + 1;
            }
            this->result_.push_back(tmp);
            return this->result_;
        }
        size_t size = 1;
        for (int i = n; i > n - k; i--) {
            size *= i;
        }
        for (int i = 2; i <= k; i++) {
            size /= i;
        }
        printf("-->size: %lu\n", size);
        this->result_.reserve(size);
        this->n_ = n;
        this->k_ = k;
        DFS(0);
        return this->result_;
    }
};
}

void TestForCombine77() {
    auto *obj = new combine77::Solution();
    auto result = obj->combine(14, 3);
    for (const auto &r:result) {
        for (auto c : r) {
            printf("%d ", c);
        }
        printf("\n");
    }
}
