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
namespace shortest_superstring {
class Solution {
    int strLength_;
    int bestLength_;
    vector<int> bestPath_;
    vector<vector<int>> minLength_;
public:
    static int Overlap(string &si, string &sj) {
        int minLen = min(si.size(), sj.size());
        for (int i = minLen - 1; i > 0; i--) {
            if (si.substr(si.size() - i) == sj.substr(0, i)) {
                return sj.length() - i;
            }
        }
        return sj.length();
    }

    void InitMinLength(vector<string> &A) {
        minLength_ = vector<vector<int>>(strLength_, vector<int>(strLength_));
        for (int i = 0; i < strLength_; ++i) {
            for (int j = 0; j < strLength_; ++j) {
                minLength_[i][j] = Overlap(A[i], A[j]);
                minLength_[j][i] = Overlap(A[j], A[i]);
            }
        }
    }

    void DFS(vector<string> &A, int depth, int used, int curLen, vector<int> &curPath) {
        if (curLen >= bestLength_) {
            return;
        }
        if (depth >= strLength_) {
            bestLength_ = curLen;
            bestPath_ = curPath;
            return;
        }
        for (int i = 0; i < strLength_; i++) {
            if (used & (1 << i)) {
                continue;
            }
            curPath[depth] = i;
            DFS(A,
                depth + 1,
                used | (1 << i),
                depth == 0 ? A[i].size() : curLen + minLength_[curPath[depth - 1]][i],
                curPath);
        }
    }

    string shortestSuperstring(vector<string> &A) {
        if (A.empty()) {
            return "";
        }
        if (A.size() == 1) {
            return A[0];
        }
        strLength_ = A.size();
        InitMinLength(A);
        bestLength_ = INT_MAX;
        bestPath_ = vector<int>(strLength_);
        vector<int> curPath(strLength_);
        int used = 0;
        DFS(A, 0, used, 0, curPath);

        string ans = A[bestPath_[0]];
        for (int i = 1; i < bestPath_.size(); ++i) {
            int pre = bestPath_[i - 1];
            int next = bestPath_[i];
            ans += A[next].substr(A[next].size() - minLength_[pre][next]);
        }
        return ans;
    }
};
}

void TestForShortesSuperString() {
    auto *obj = new shortest_superstring::Solution();
    vector<string> strs{"catg", "ctaagt", "gcta", "ttca", "atgcatc"};
    auto result = obj->shortestSuperstring(strs);
    printf("%s\n", result.c_str());
}
