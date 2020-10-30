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
namespace generate_parenth {
class Solution {
    vector<vector<string>> dp_;
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0) {
            return vector<string>();
        }
        dp_ = vector<vector<string>>(n + 1, vector<string>());
        dp_[0].push_back("");
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                for (const auto &q : dp_[j]) {
                    for (const auto &p : dp_[i - 1 - j]) {
                        dp_[i].push_back("(" + q + ")" + p);
                    }
                }
            }
        }
        return dp_[n];
    }
};

class Solution_DFS {
    vector<string> res_;
public:
    void DFS(int target, int left, int state, string &context) {
        if (state >= target) {
            if (left == 0) {
                res_.push_back(context);
                return;
            }
            return;
        }
        // state < target
        if (left + state * 2 >= target * 2) {
            return;
        }
        if (left > 0) {
            // put right
            context.push_back(')');
            DFS(target, left - 1, state + 1, context);
            context.pop_back();
        }
        // put left
        context.push_back('(');
        DFS(target, left + 1, state, context);
        context.pop_back();
    }

    vector<string> generateParenthesis(int n) {
        string context;
        DFS(n, 0, 0, context);
        return res_;
    }
};
}

void TestForGenerateParenth() {
    auto *obj = new generate_parenth::Solution();
    auto result = obj->generateParenthesis(3);
    for (auto &s : result) {
        printf("%s\n", s.c_str());
    }
}
