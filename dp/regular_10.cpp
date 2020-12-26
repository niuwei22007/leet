#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;
namespace regular {
class Solution {
public:
    // bool IsMatch_Failed(const string& s, int si, const string& p, int pi) {
    //     if (si == s.size() && pi == p.size()) {
    //         return true;
    //     }
    //     if (pi == p.size()) {
    //         return false;
    //     }
    //     if (si == s.size()) {
    //         if ((p.size() - pi) % 2 == 1) {
    //             return false;
    //         }
    //         while ((pi + 1) < p.size() && p[pi + 1] == '*') {
    //             pi += 2;
    //         }
    //         return pi == p.size();
    //     }
    //     if (s[si] == p[pi] || p[pi] == '.') {
    //         return IsMatch_Failed(s, si + 1, p, pi + 1);
    //     }
    //     if (p[pi] == '*') {
    //         while (si < s.size() && (s[si] == p[pi - 1] || p[pi - 1] == '.')) {
    //             if (IsMatch_Failed(s, si, p, pi + 1)) {
    //                 return true;
    //             }
    //             si++;
    //         }
    //         return IsMatch_Failed(s, si, p, pi + 1);
    //     }
    //     if (pi < p.size() && p[pi + 1] == '*') {
    //         return IsMatch_Failed(s, si, p, pi + 2);
    //     }
    //     return false;
    // }
    //
    // bool isMatch_Failed(string s, string p) {
    //     if (p == ".*") {
    //         return true;
    //     }
    //     return IsMatch_Failed(s, 0, p, 0);
    // }

    bool IsSame(char a, char b) {
        return a == b || b == '.';
    }

    bool isMatch(string s, string p) {
        if (p == ".*") {
            return true;
        }
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;

        for (int j = 2; j < m + 1; j++) {
            dp[0][j] = (p[j - 1] == '*' && dp[0][j - 2]);
        }

        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                if (IsSame(s[i - 1], p[j - 1])) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*' && j > 1) {
                    if (!IsSame(s[i - 1], p[j - 2])) {
                        dp[i][j] = dp[i][j - 2];
                    } else {
                        dp[i][j] = dp[i][j - 2] || dp[i][j - 1] || dp[i - 1][j];
                    }
                }
            }
        }
        return dp[n][m];
    }
};
}

void TestForRegular() {
    auto* obj = new regular::Solution();
    vector<pair<string, string>> inputs = {
        // {"aa",          "a"},
        // {"aa",          "a*"},
        // {"aab",         "c*a*b"},
        // {"ab",          ".*"},
        // {"mississippi", "mis*is*p*."},
        // {"aaaa",        "aaaaa"},
        // {"aaaa",        "a*a"},
        // {"aaa",   "ab*a*c*a"},
        // {"a",     "ab*"},
        {"bbbba", ".*a*a"},

    };
    for (auto& i : inputs) {
        auto res = obj->isMatch(i.first, i.second);
        printf("%d\n", res);
    }
}
