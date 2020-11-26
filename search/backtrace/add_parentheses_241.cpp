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
namespace parentheses {
class Solution {
public:
    static inline bool IsOps(char c) {
        return c == '+' || c == '-' || c == '*';
    }

    vector<int> Calculate(vector<int>& forms, int left, int right) {
        if ((right - left) == 1) {
            return {forms[left]};
        }
        vector<int> res;
        for (int i = left; i < right; i++) {
            if (i % 2 == 1) {
                vector<int> leftRes = Calculate(forms, left, i);
                vector<int> rightRes = Calculate(forms, i + 1, right);
                for (auto lr : leftRes) {
                    for (auto rr : rightRes) {
                        switch (forms[i]) {
                            case '+':
                                res.push_back(lr + rr);
                                break;
                            case '-':
                                res.push_back(lr - rr);
                                break;
                            case '*':
                                res.push_back(lr * rr);
                                break;
                        }
                    }
                }
            }
        }
        return res;
    }

    vector<int> diffWaysToCompute(string input) {
        if (input.empty()) {
            return {};
        }
        vector<int> forms;
        istringstream in(input);
        while (true) {
            int num = -1;
            in >> num;
            if (num < 0) {
                break;
            }
            forms.push_back(num);
            char opt = 0;
            in >> opt;
            if (!IsOps(opt)) {
                break;
            }
            forms.push_back(opt);
        }
        return Calculate(forms, 0, forms.size());
    }
};
}

void TestForAddParentheses() {
    auto* obj = new parentheses::Solution();
    auto res = obj->diffWaysToCompute("2-1-1");
    for (const int& r : res) {
        printf("%d\n", r);
    }
}
