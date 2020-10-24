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
namespace letter784 {
class Solution {
    vector<string> result_;
public:
    static inline void Change(string &s, int i) {
        if (islower(s[i])) {
            s[i] = s[i] - 'a' + 'A';
        } else {
            s[i] = s[i] - 'A' + 'a';
        }
    }

    void DFS(string &s, int start, int end) {
        result_.push_back(s);
        for (int i = start; i < end; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                continue;
            }
            Change(s, i);
            DFS(s, i + 1, end);
            Change(s, i);
        }
    }

    void FOR(string &s, int start, int end) {
        result_.push_back(s);
        for (int i = 0; i < end; ++i) {
            if (s[i] <= '9') {
                continue;
            }
            for (int j = result_.size() - 1; j >= 0; j--) {
                string tmp = result_[j];
                Change(tmp, i);  // tmp ^= 1 << 5;
                result_.emplace_back(std::move(tmp));
            }
        }
    }

    vector<string> letterCasePermutation(string S) {
//        DFS(S, 0, S.size());
        FOR(S, 0, S.size());
        return result_;
    }
};
}

void TestForLetterPermutation() {
    auto *obj = new letter784::Solution();
    auto result = obj->letterCasePermutation("abz");
    for (const auto &r:result) {
        printf("%s\n", r.c_str());
    }
}
