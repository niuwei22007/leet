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
namespace palindorme {
class Solution {
    unordered_map<string, bool> dict_;
public:
    bool Check(const string& s) {
        if (dict_.find(s) != dict_.end()) {
            return dict_[s];
        }
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - 1 - i]) {
                dict_[s] = false;
                return false;
            }
        }
        dict_[s] = true;
        return true;
    }

    void Partition(const string& s, int startIndex, vector<vector<string>>& ans, vector<string>& tmp) {
        if (startIndex >= s.size()) {
            ans.push_back(tmp);
            return;
        }
        for (int i = 1; i <= (s.size() - startIndex); i++) {
            string sub = s.substr(startIndex, i);
            if (Check(sub)) {
                tmp.push_back(sub);
                Partition(s, startIndex + i, ans, tmp);
                tmp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> tmp;
        Partition(s, 0, ans, tmp);
        return ans;
    }
};
}

void TestForPalindorme() {
    auto* obj = new palindorme::Solution();
    auto res = obj->partition("aabceabc");
    for (const vector<string>& rs : res) {
        for (const string& r:rs) {
            printf("%s ", r.c_str());
        }
        printf("\n");
    }
}
