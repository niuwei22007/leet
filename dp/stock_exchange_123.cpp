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
}

void TestForExchangeStock3() {
    auto* obj = new stock_exchange3::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    auto res = obj->maxProfit(cost);
    printf("%d\n", res);
}
