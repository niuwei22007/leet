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
namespace stock_exchange {
class Solution {
public:
    int maxProfit_Common(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        int len = prices.size();
        vector<int> minVal(len, 0);
        vector<int> maxVal(len, 0);
        minVal[0] = prices[0];
        maxVal[len - 1] = prices[len - 1];
        int right;
        for (int left = 0; left < len; left++) {
            if (left > 0) {
                minVal[left] = min(prices[left], minVal[left - 1]);
                right = len - left - 1;
                maxVal[right] = max(prices[right], prices[right + 1]);
            }
        }
        int ans = 0;
        for (int i = 0; i < len; i++) {
            ans = max(ans, (maxVal[i] - minVal[i]));
        }
        return ans;
    }

    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        int curMin = prices[0];
        int maxPro = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < curMin) {
                curMin = prices[i];
            } else {
                maxPro = max(maxPro, prices[i] - curMin);
            }
        }
        return maxPro;
    }
};
}

void TestForExchangeStock() {
    auto* obj = new stock_exchange::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
}
