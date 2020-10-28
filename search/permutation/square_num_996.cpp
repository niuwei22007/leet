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
namespace square_num {
class Solution {
    int ans_;
    map<int, int> count_;
    vector<int> nodes_;
    map<int, vector<int>> graph_;
public:
    bool IsSquare(int a, int b) {
        int c = sqrt(a + b);
        return c * c == a + b;
    }

    void DFS(vector<int> &A, int dep, int value) {
        if (dep == A.size()) {
            ans_++;
            return;
        }
        for (auto &n : graph_[value]) {
            if (count_[n] > 0) {
                count_[n]--;
                DFS(A, dep + 1, n);
                count_[n]++;
            }
        }
    }

    int numSquarefulPerms(vector<int> &A) {
        if (A.empty()) {
            return 0;
        }
        if (A.size() == 1) {
            return 1;
        }
        for (int &i : A) {
            count_[i]++;
        }

        for (auto n : count_) {
            nodes_.push_back(n.first);
        }

        for (int i = 0; i < nodes_.size(); i++) {
            int valueI = nodes_[i];
            if (count_[valueI] > 1 && IsSquare(valueI, valueI)) {
                graph_[valueI].push_back(valueI);
            }
            for (int j = i + 1; j < nodes_.size(); j++) {
                int valueJ = nodes_[j];
                if (count_[valueJ] > 0 && IsSquare(valueI, valueJ)) {
                    graph_[valueI].push_back(valueJ);
                    graph_[valueJ].push_back(valueI);
                }
            }
        }

        for (int i = 0; i < nodes_.size(); i++) {
            int value = nodes_[i];
            count_[value]--;
            DFS(A, 1, value);
            count_[value]++;
        }
        return ans_;
    }
};

class Solution1 {
    int ans_;
public:
    bool IsSquare(int a, int b) {
        int c = sqrt(a + b);
        return c * c == a + b;
    }

    void DFS(vector<int> &A, int dep, int prev, vector<bool> &used) {
        if (dep == A.size()) {
            ans_++;
            return;
        }
        for (int i = 0; i < A.size(); i++) {
            if (used[i] || (i > 0 && !used[i - 1] && A[i] == A[i - 1])) {
                continue;
            }
            if (prev != -1 && !IsSquare(A[i], A[prev])) {
                continue;
            }
            used[i] = true;
            DFS(A, dep + 1, i, used);
            used[i] = false;
        }
    }

    int numSquarefulPerms(vector<int> &A) {
        if (A.empty()) {
            return 0;
        }
        if (A.size() == 1) {
            return 1;
        }
        sort(A.begin(), A.end());
        ans_ = 0;
        vector<bool> used(A.size(), false);
        DFS(A, 0, -1, used);
        return ans_;
    }
};
}

void TestForSquareNum() {
    auto *obj = new square_num::Solution();
    vector<int> strs{1, 2, 3};
    auto result = obj->numSquarefulPerms(strs);
    printf("%d\n", result);
}
