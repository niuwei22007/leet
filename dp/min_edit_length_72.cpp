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
namespace min_edit_length {
class Solution {
public:
    int minDistance(string& word1, int i1, string& word2, int i2, vector<vector<int>>& memo) {
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

    int minDistance(string word1, string word2) {
        vector<vector<int>> memo(word1.size(), vector<int>(word2.size(), -1));
        return minDistance(word1, word1.size() - 1, word2, word2.size() - 1, memo);
    }
};
}

void TestForMinEditLength() {
    auto* obj = new min_edit_length::Solution();
    auto res = obj->minDistance("horse", "ros");
    printf("%d\n", res);
}
