//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;
namespace invalid_parenth {
class Solution {
    vector<string> ans_;
public:
    static bool IsValid(string &s) {
        int left = 0;
        for (char i : s) {
            if (i == '(') {
                left++;
            } else if (i == ')') {
                left--;
            }
            if (left < 0) {
                return false;
            }
        }
        return left == 0;
    }

    static inline string RemoveByIndex(string &s, int i) {
        if (i == 0) {
            return s.substr(1);
        } else if (i == s.size() - 1) {
            return s.substr(0, i);
        }
        return s.substr(0, i) + s.substr(i + 1);
    }

    void DFS(string &s, int index, int left, int right) {
        if (left == 0 && right == 0) {
            if (IsValid(s)) {
                ans_.push_back(s);
            }
            return;
        }
        for (int i = index; i < s.size(); i++) {
            if (i > index && s[i] == s[i - 1]) {
                continue;
            }
            if (left > 0 && s[i] == '(') {
                string tmp = RemoveByIndex(s, i);
                DFS(tmp, i, left - 1, right);
            }
            if (right > 0 && s[i] == ')') {
                string tmp = RemoveByIndex(s, i);
                DFS(tmp, i, left, right - 1);
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        if (s.empty()) {
            vector<string> tmp{""};
            return tmp;
        }
        int left = 0, right = 0;
        for (auto i : s) {
            if (i == '(') {
                left++;
            } else if (i == ')') {
                if (left > 0) {
                    left--;
                } else {
                    right++;
                }
            }
        }
        DFS(s, 0, left, right);
        return ans_;
    }
};
}

void TestForInvalidParenth() {
    auto *obj = new invalid_parenth::Solution();
    auto result = obj->removeInvalidParentheses("(a)())()");
    for (auto &s : result) {
        printf("%s\n", s.c_str());
    }
}
