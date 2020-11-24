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
public:
    bool Check(const string& s, int i, int j) {
        if (j < i)
            return true;
        if (s[i++] == s[j--])
            return Check(s, i, j);
        else
            return false;
    }

    void Partition(const string& s, int startIndex, vector<vector<string>>& ans, vector<string>& tmp) {
        if (startIndex >= s.size()) {
            ans.push_back(tmp);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            string sub = s.substr(startIndex, i - startIndex + 1);
            if (Check(s, startIndex, i)) {
                tmp.push_back(sub);
                Partition(s, i + 1, ans, tmp);
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
