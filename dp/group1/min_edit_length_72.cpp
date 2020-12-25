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
#include <stack>

using namespace std;
namespace min_edit_length {
class Solution {
public:
    int minDistance_DFS(string& word1, int i1, string& word2, int i2, vector<vector<int>>& memo) {
        if (i1 == -1 || i2 == -1) {
            return max(i1, i2) + 1;
        }
        if (memo[i1][i2] > -1) {
            return memo[i1][i2];
        }
        if (word1[i1] == word2[i2]) {
            memo[i1][i2] = minDistance(word1, i1 - 1, word2, i2 - 1, memo);
        } else {
            int add = minDistance(word1, i1, word2, i2 - 1, memo);
            int del = minDistance(word1, i1 - 1, word2, i2, memo);
            int rep = minDistance(word1, i1 - 1, word2, i2 - 1, memo);
            memo[i1][i2] = 1 + min(min(add, del), rep);
        }
        return memo[i1][i2];
    }

    int minDistance_DFS(string word1, string word2) {
        vector<vector<int>> memo(word1.size(), vector<int>(word2.size(), -1));
        return minDistance_DFS(word1, word1.size() - 1, word2, word2.size() - 1, memo);
    }

    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        int dp[n + 1][m + 1];
        for (int i = 0; i < n + 1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i < m + 1; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
                }
            }
        }
        return dp[n][m];
    }
};
}

void TestForMinEditLength() {
    auto* obj = new min_edit_length::Solution();
    auto res = obj->minDistance("horse", "ros");
    printf("%d\n", res);
}
