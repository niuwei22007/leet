#include "../trust.h"
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
namespace stock_exchange3 {
class Solution_DFS {
    struct tuple_hash {
        size_t operator()(const tuple<int, int, int>& p) const {//别忘记const
            return hash<int>()(get<0>(p)) ^ hash<int>()(get<1>(p)) ^ hash<int>()(get<2>(p));
        }
    };

    struct tuple_equal {
        bool operator()(const tuple<int, int, int>& a, const tuple<int, int, int>& b) const {
            return get<0>(a) == get<0>(b) &&
                   get<1>(a) == get<1>(b) &&
                   get<2>(a) == get<2>(b);
        }
    };

    unordered_map<tuple<int, int, int>, int, tuple_hash, tuple_equal> cache;
public:
    int DFS(vector<int>& prices, int index, int status, int times) {
        auto tp = make_tuple(index, status, times);
        if (cache.find(tp) != cache.end()) {
            return cache[tp];
        }
        if (index == prices.size() || times == 2) {
            return 0;
        }
        // hold
        int hold = DFS(prices, index + 1, status, times);
        int sell = 0, buy = 0;
        if (status == 1) {
            // sell
            sell = DFS(prices, index + 1, 0, times + 1) + prices[index];
        } else {
            buy = DFS(prices, index + 1, 1, times) - prices[index];
        }
        cache[tp] = max(hold, max(sell, buy));
        return cache[tp];
    }

    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        return DFS(prices, 0, 0, 0);
    }
};

class Solution_DP {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int dp[n][3][2];
        dp[0][0][0] = 0; // 0 sell
        dp[0][0][1] = -prices[0]; // 1 buy

        dp[0][1][0] = 0; // 1 sell
        dp[0][1][1] = -prices[0]; // 2 buy

        dp[0][2][0] = 0; // 2 sell
        dp[0][2][1] = -prices[0]; // 3 buy

        for (int i = 1; i < n; i++) {
            dp[i][0][0] = dp[i - 1][0][0];
            dp[i][0][1] = max(dp[i - 1][0][1], dp[i - 1][0][0] - prices[i]);
            dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][0][1] + prices[i]);
            dp[i][1][1] = max(dp[i - 1][1][1], dp[i - 1][1][0] - prices[i]);
            dp[i][2][0] = max(dp[i - 1][2][0], dp[i - 1][1][1] + prices[i]);
        }

        int max0 = max(dp[n - 1][0][0], dp[n - 1][0][1]);
        int max1 = max(dp[n - 1][1][0], dp[n - 1][1][1]);
        return max(max(max0, max1), dp[n - 1][2][0]);
    }
};

class Solution_Compress {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int pre00 = 0, cur00 = 0;
        int pre01 = -prices[0], cur01 = 0;
        int pre10 = 0, cur10 = 0;
        int pre11 = -prices[0], cur11 = 0;
        int pre20 = 0, cur20 = 0;

        for (int i = 1; i < n; i++) {
            cur00 = pre00;
            cur01 = max(pre01, pre00 - prices[i]);
            cur10 = max(pre10, pre01 + prices[i]);
            cur11 = max(pre11, pre10 - prices[i]);
            cur20 = max(pre20, pre11 + prices[i]);

            pre00 = cur00;
            pre01 = cur01;
            pre10 = cur10;
            pre11 = cur11;
            pre20 = cur20;
        }

        int max0 = max(cur00, cur01);
        int max1 = max(cur10, cur11);
        return max(max(max0, max1), cur20);
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int pre00 = 0;
        int pre01 = -prices[0];
        int pre10 = 0;
        int pre11 = -prices[0];
        int pre20 = 0;

        for (int i = 1; i < n; i++) {
            // cur00 = pre00;
            pre01 = max(pre01, pre00 - prices[i]);
            pre10 = max(pre10, pre01 + prices[i]);
            pre11 = max(pre11, pre10 - prices[i]);
            pre20 = max(pre20, pre11 + prices[i]);
        }

        int max0 = max(pre00, pre01);
        int max1 = max(pre10, pre11);
        return max(max(max0, max1), pre20);
    }
};
}

void TestForExchangeStock3() {
    auto* obj = new stock_exchange3::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
}
