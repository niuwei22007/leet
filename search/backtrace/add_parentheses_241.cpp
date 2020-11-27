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

    vector<int> diffWaysToCompute_Recursion(string input) {
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

    static inline int Cal(int a, char op, int b) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
        }
        return INT_MAX;
    }

    vector<int> diffWaysToCompute(string input) {
        if (input.empty()) {
            return {};
        }
        vector<int> nums;
        vector<char> ops;
        istringstream in(input);
        while (true) {
            int num = -1;
            in >> num;
            if (num < 0) {
                break;
            }
            nums.push_back(num);
            char opt = 0;
            in >> opt;
            if (!IsOps(opt)) {
                break;
            }
            ops.push_back(opt);
        }
        // return Calculate(forms, 0, forms.size());
        int n = nums.size();
        vector<int> dp[n][n];
        // 初始化和计算紧邻1个操作符的结果
        dp[0][0].push_back(nums[0]);
        for (int i = 1; i < n; i++) {
            dp[i][i].push_back(nums[i]);
            dp[i - 1][i].push_back(Cal(nums[i - 1], ops[i - 1], nums[i]));
        }
        // 计算紧邻2 ~ (n-1)个操作符的结果
        for (int dist = 2; dist < n; dist++) {
            // 从下标0开始计算
            for (int numIndex = 0; numIndex < (n - dist); numIndex++) {
                // 遍历每个操作符，并分成左右两部分计算结果
                for (int op = 0; op < dist; op++) {
                    // 遍历左操作数
                    for (auto left : dp[numIndex][numIndex + op]) {
                        // 遍历右操作数
                        for (auto right : dp[numIndex + op + 1][numIndex + dist]) {
                            int tmp = Cal(left, ops[numIndex + op], right);
                            dp[numIndex][numIndex + dist].push_back(tmp);
                        }
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};
}

void TestForAddParentheses() {
    auto* obj = new parentheses::Solution();
    auto res = obj->diffWaysToCompute("2*3-4*5");
    for (const int& r : res) {
        printf("%d\n", r);
    }
}
