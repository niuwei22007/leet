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
namespace restore_ip {
class Solution {
    unordered_set<string> validSet_;
    vector<string> ans_;

    static string Join(vector<string>& ips) {
        string res;
        for (auto& i:ips) {
            res.append(i);
            res.append(".");
        }
        res.pop_back();
        return move(res);
    }

    void InitSet() {
        for (int i = 0; i <= 255; i++) {
            validSet_.insert(to_string(i));
        }
    }

    inline bool Valid(const string& s) {
        return validSet_.count(s) > 0;
    }

    void Partition(const string& s, int startIndex, vector<string>& tmp) {
        int n = s.size();
        if (startIndex == n) {
            if (tmp.size() == 4) {
                ans_.push_back(Join(tmp));
            }
            return;
        }
        if ((n - startIndex) > 3 * (4 - tmp.size())) {
            return;
        }
        int len = tmp.size() == 3 ? (n - startIndex) : 1;
        int index = startIndex + len;
        while (index <= n && len <= min(3, n - startIndex)) {
            string subStr = s.substr(startIndex, len);
            if (!Valid(subStr)) {
                break;
            }
            tmp.push_back(subStr);
            Partition(s, index, tmp);
            tmp.pop_back();
            if (s[startIndex] == '0') {
                break;
            }
            len++;
            index = startIndex + len;
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        if (s.length() < 4) {
            return ans_;
        }
        InitSet();
        vector<string> tmp;
        Partition(s, 0, tmp);
        return ans_;
    }
};
}

void TestForRestoreIp() {
    auto* obj = new restore_ip::Solution();
    auto res = obj->restoreIpAddresses("101023");
    for (const string& r : res) {
        printf("%s\n", r.c_str());
    }
}
