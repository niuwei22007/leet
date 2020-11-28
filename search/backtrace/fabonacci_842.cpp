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
namespace fabonacci {
class Solution {
public:
    static inline long LastSum(vector<int>& ans) {
        if (ans.size() >= 2) {
            size_t len = ans.size();
            return (long)ans[len - 1] + ans[len - 2];
        }
        return -1;
    }

    bool Backtracking(string& s, int index, vector<int>& ans) {
        if (ans.size() >= 3) {
            size_t len = ans.size();
            long left = (long)ans[len - 2] + ans[len - 3];
            if (left > INT_MAX || left != ans[len - 1]) {
                return false;
            }
            if (index == s.length()) {
                return true;
            }
        }
        for (int i = index; i < s.length(); i++) {
            string tmp = s.substr(index, i - index + 1);
            unsigned long tmpVal = stoul(tmp);
            if (tmpVal > INT_MAX) {
                return false;
            }
            long lastSum = LastSum(ans);
            if (lastSum > -1 && lastSum < tmpVal) {
                return false;
            }
            ans.push_back(tmpVal);
            if (Backtracking(s, i + 1, ans)) {
                return true;
            }
            ans.pop_back();
            if (tmpVal == 0) {
                return false;
            }
        }
        return false;
    }

    vector<int> splitIntoFibonacci(string S) {
        vector<int> ans;
        if (S.empty() || S.length() < 3) {
            return ans;
        }
        if (!Backtracking(S, 0, ans)) {
            ans.clear();
        }
        return ans;
    }
};
}

void TestForSplitFabonacci() {
    auto* obj = new fabonacci::Solution();
    auto res = obj->splitIntoFibonacci("214748364721474836422147483641");
    for (const auto& r : res) {
        printf("%d ", r);
    }
}
