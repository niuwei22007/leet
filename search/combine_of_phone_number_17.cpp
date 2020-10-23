//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
namespace phonenumber {
static map<char, string> TABLE = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"},
};

class Solution {
    vector<string> result_;
    string digits_;
    int digitLen_;
public:
    void DFS(int i, string &res) {
        if (i == this->digitLen_) {
            this->result_.push_back(res);
            return;
        }
        for (char c : TABLE[this->digits_[i]]) {
            res.append(1, c);
            DFS(i + 1, res);
            res.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return this->result_;
        }
        this->digits_ = digits;
        this->digitLen_ = digits.length();
        string res;
        res.reserve(1000);
        DFS(0, res);
        return this->result_;
    }
};
}

void TestForPhoneNumber() {
    auto *obj = new phonenumber::Solution();
    auto result = obj->letterCombinations("29");
    for (const auto &r:result) {
        printf("%s\n", r.c_str());
    }
}
