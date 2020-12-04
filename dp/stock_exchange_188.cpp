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
namespace stock_exchange4 {
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        int n = prices.size();
        int m = 2 * k + 1;
        vector<int> dp(m, 0);
        for (int i = 0; i < m; i++) {
            dp[i] = ((i % 2) == 0) ? 0 : -prices[0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                int status = (i % 2) == 0 ? 1 : -1;
                dp[j] = max(dp[j], dp[j - 1] + prices[i] * status);
            }
        }

        int ans = dp[0];
        for (int i = 1; i < m; i++) {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
}

void TestForExchangeStock4() {
    auto* obj = new stock_exchange4::Solution();
    vector<int> cost{3, 3, 5, 0, 0, 3, 1, 4};
    int k = 2;
    auto res = obj->maxProfit(k, cost);
    printf("%d\n", res);
}
