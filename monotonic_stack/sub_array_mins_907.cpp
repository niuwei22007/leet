//
// Created by 鞋底洞 on 2020/10/22.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;
namespace subarray {
class Solution {
private:
    const int mod = 1e9 + 7;
public:
    int sumSubarrayMins(vector<int> &A) {
        stack<int> inc_stack; //单调递增栈, 存储的是数组A的索引
        A.push_back(-1); //保证栈里所有元素都弹出
        int len = A.size();
        // {__n__    A[i]    ___m____ };    如 8, 4, 6, 5, 7, 9, 3, 0 -> 对于A[i] = 5, n = 1 ([6]), m = 2 ([7, 9])
        // A[i]左侧有n个连续的大于A[i]的数, 右侧有连续m个大于A[i]的数, 则A[i]作为最小值的数组个数为(m+1)*(n+1)
        // 关键即为找到每个A[i]对应的区间, 满足A[i]为该区间内的最小值
        int ans = 0;
        for (int i = 0; i < len; i++) {
            while (!inc_stack.empty() && A[inc_stack.top()] >= A[i]) { // A[i]比栈顶元素小, 说明栈顶元素的区间截止, 该处理栈顶元素
                int index = inc_stack.top(); //取栈顶索引
                inc_stack.pop();
                int pre = index - (inc_stack.empty() ? -1 : inc_stack.top()); //对应n+1
                int after = i - index;   //对应m+1
                ans += A[index] * pre * after;   //A[i]作为最小值的次数为(m+1)*(n+1), 即ans加上A[i]*(m+1)*(n+1)
                ans %= mod;
            }
            inc_stack.push(i);
        }
        return ans;
    }
};
}

void TestForSubArray() {
    auto *obj = new subarray::Solution();
    vector<int> subarray = {3, 1, 2, 4};
    auto res = obj->sumSubarrayMins(subarray);
    printf("result: %d", res);
}
