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
namespace stock_exchange2 {
class Solution {
public:
    int maxProfit_DP(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int dp[n][2];
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }

    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int preNone = 0;
        int preHas = -prices[0];
        int curNone;
        int curHas;
        for (int i = 1; i < n; i++) {
            curNone = max(preNone, preHas + prices[i]);
            curHas = max(preHas, preNone - prices[i]);
            preNone = curNone;
            preHas = curHas;
        }
        return curNone;
    }
};
}

void TestForExchangeStock2() {
    auto* obj = new stock_exchange2::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
    res = obj->maxProfit_DP(cost);
    printf("%d\n", res);
}
