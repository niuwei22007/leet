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
        return 0;
    }
};
}

void TestForExchangeStock4() {
    auto* obj = new stock_exchange4::Solution();
    vector<int> cost{7, 1, 5, 3, 0, 6, 4, 9};
    int k = 2;
    auto res = obj->maxProfit(k, cost);
    printf("%d\n", res);
}
