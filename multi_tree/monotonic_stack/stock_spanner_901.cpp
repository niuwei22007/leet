//
// Created by 鞋底洞 on 2020/10/22.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;
namespace stockspanner {
class StockSpanner {
    stack<pair<int, int>> stock;
public:
    StockSpanner() {

    }

    int next(int price) {
        int spanner = 1;
        while (!stock.empty() && stock.top().first <= price) {
            spanner += stock.top().second;
            stock.pop();
        }
        stock.push(make_pair(price, spanner));
        return spanner;
    }
};
}

void TestForStockSpanner() {
    auto *obj = new stockspanner::StockSpanner();
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    for (auto s: prices) {
        printf("%d\n", obj->next(s));
    }
}
