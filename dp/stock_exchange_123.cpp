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
class Solution {
public:
    int DFS(vector<int>& prices, int index, int status, int times) {
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
        return max(hold, max(sell, buy));
    }
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }
        return DFS(prices, 0, 0, 0);
    }
};
}

void TestForExchangeStock3() {
    auto* obj = new stock_exchange3::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
}
