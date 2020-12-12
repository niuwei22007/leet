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

using namespace std;
namespace split_word2 {
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> charSet(allowed.begin(), allowed.end());
        int count = 0;
        for (auto& word: words) {
            bool consis = true;
            for (auto c : word) {
                if (charSet.count(c) == 0) {
                    consis = false;
                    break;
                }
            }
            count += consis;
        }
        return count;
    }

    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int len = nums.size();
        vector<int> allSum(len, 0);
        for (int i = 0; i < len; i++) {
            allSum[i] = nums[i] + ((i == 0) ? 0 : allSum[i - 1]);
        }
        vector<int> res(len, 0);
        for (int i = 0; i < len; i++) {
            if (i == 0) {
                res[i] = allSum[len - 1] - nums[i] * len;
            } else {
                res[i] = (nums[i] * i - allSum[i - 1]) + (allSum[len - 1] - allSum[i - 1] - nums[i] * (len - i));
            }
        }
        return res;
    }

    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int len = aliceValues.size();
        vector<int> abSub(len);
        for (int i = 0; i < len; i++) {
            abSub[i] = aliceValues[i] + bobValues[i];
        }

        sort(abSub.begin(), abSub.end(), greater<>());
        int a = 0;
        int b = 0;
        for (int i = 0; i < len; i++) {
            if (i % 2 == 0) {
                a += abSub[i];
            } else {
                b += abSub[i];
            }
            a += aliceValues[i];
            b += bobValues[i];
        }
        int score = a - b;
        if (score > 0) {
            return 1;
        }
        if (score == 0) {
            return 0;
        }
        return -1;
    }
};
}

void TestForSplitWord2() {
    auto* obj = new split_word2::Solution();
    // string s = "pineapplepenapple";
    // vector<string> dict{"apple", "pen", "applepen", "pine", "pineapple"};
    string s = "aaaaaaa";
    vector<string> dict{"aaaa", "aaa"};
    // string s = "catsanddog";
    // vector<string> dict{"cat", "cats", "and", "sand", "dog"};

    auto res = obj->countConsistentStrings(s, dict);
    vector<int> aa{2, 3, 5};
    auto ss = obj->getSumAbsoluteDifferences(aa);

    vector<int> a{1, 2};
    vector<int> b{3, 1};
    res = obj->stoneGameVI(a, b);
    printf("%d\n", res);
}
