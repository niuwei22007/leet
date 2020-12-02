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
namespace range_sum {
class NumArray {
    vector<int> sums_;
public:
    NumArray(vector<int>& nums) {
        if (!nums.empty()) {
            sums_ = vector<int>(nums.size(), 0);
            sums_[0] = nums[0];
            for (int i = 1; i < nums.size(); i++) {
                sums_[i] = nums[i] + sums_[i - 1];
            }
        }
    }

    int sumRange(int i, int j) {
        if (j >= sums_.size() || sums_.empty()) {
            return 0;
        }
        if (i == 0) {
            return sums_[j];
        }
        return sums_[j] - sums_[i - 1];
    }
};
}

void TestForRangeSum() {
    vector<int> cost{};
    auto* obj = new range_sum::NumArray(cost);
    auto res = obj->sumRange(2, 5);
    printf("%d\n", res);
}
