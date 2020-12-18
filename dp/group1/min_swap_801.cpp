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
namespace min_swap {
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        int dp[n][2];
        dp[0][0] = 0;
        dp[0][1] = 1;
        for (int i = 1; i < n; i++) {
            if (A[i - 1] < A[i] && B[i - 1] < B[i]) {
                if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
                    dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                    dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
                } else {
                    dp[i][0] = dp[i - 1][0];
                    dp[i][1] = dp[i - 1][1] + 1;
                }
            } else {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = dp[i - 1][0] + 1;
            }
        }
        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};
}

void TestForMinSwap() {
    auto* obj = new min_swap::Solution();
    // vector<int> A{0, 2, 5, 8, 9, 10, 12, 14, 18, 19, 20, 20, 24, 27, 28, 31, 33, 34, 36, 38};
    // vector<int> B{1, 2, 5, 7, 8, 9, 11, 17, 15, 16, 19, 21, 28, 29, 30, 31, 33, 34, 38, 39};
    vector<int> A{0, 7, 8, 10, 10, 11, 12, 13, 19, 18};
    vector<int> B{4, 4, 5, 7, 11, 14, 15, 16, 17, 20};
    auto res = obj->minSwap(A, B);
    printf("%d\n", res);
}
