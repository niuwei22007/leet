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
namespace stock_exchange5 {
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
        dp[1][0] = max(dp[0][0], dp[0][1] + prices[1]);
        dp[1][1] = max(dp[0][1], -prices[1]);
        for (int i = 2; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
        }
        return dp[n - 1][0];
    }

    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int preSell = max(0, prices[1] - prices[0]);
        int preBuy = max(-prices[0], -prices[1]);
        int curSell = 0;
        int curBuy = 0;
        int prePreSell = 0;

        for (int i = 2; i < n; i++) {
            curSell = max(preSell, preBuy + prices[i]);
            curBuy = max(preBuy, prePreSell - prices[i]);
            prePreSell = preSell;
            preSell = curSell;
            preBuy = curBuy;
        }
        return preSell;
    }
};
}

void TestForExchangeStock5() {
    auto* obj = new stock_exchange5::Solution();
    vector<int> cost{1, 2};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
}
