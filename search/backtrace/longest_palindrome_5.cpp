#include "../../trust.h"
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

using namespace std;
namespace longest_palindrome {
class Solution {
    static const size_t LEN = 1000;
public:
    string longestPalindrome(string s) {
        if (s.size() < 2) {
            return s;
        }
        int len = s.size();
        bool dp[LEN][LEN];
        for (int i = 0; i < len; i++) {
            dp[i][i] = true;
        }
        int maxLen = 1;
        int start = 0;
        for (int j = 1; j < len; ++j) {
            for (int i = 0; i < j; i++) {
                if (s[i] != s[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                    if (dp[i][j] && (j - i + 1) > maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};
}

void TestForLongestPalindrome() {
    auto* obj = new longest_palindrome::Solution();
    auto res = obj->longestPalindrome("babad");
    // for (const string& r : res) {
    printf("%s\n", res.c_str());
    // }
}
