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
namespace partition_subset {
class Solution {
    bool Partition(vector<int>& nums, vector<int>& subSet, int subSum, int startIndex) {
        if (startIndex < 0) {
            return true;
        }
        int seleteced = nums[startIndex];
        for (int i = 0; i < subSet.size(); i++) {
            if (subSet[i] + seleteced <= subSum) {
                subSet[i] += seleteced;
                if (Partition(nums, subSet, subSum, startIndex - 1)) {
                    return true;
                }
                subSet[i] -= seleteced;
            }
            if (subSet[i] == 0) {
                break;
            }
        }
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum % k != 0) {
            return false;
        }
        int subSum = sum / k;
        sort(nums.begin(), nums.end());
        size_t startIndex = nums.size() - 1;
        if (nums[startIndex] > subSum) {
            return false;
        }
        while (startIndex >= 0 && nums[startIndex] == subSum) {
            startIndex--;
            k--;
        }
        vector<int> subSets(k, 0);
        return Partition(nums, subSets, subSum, startIndex);
    }
};
}

void TestForPartitionSubsets() {
    auto* obj = new partition_subset::Solution();
    vector<int> matrix{4, 3, 2, 3, 5, 2, 1};
    int k = 4;
    auto res = obj->canPartitionKSubsets(matrix, k);
    printf("%s", res ? "true" : "false");
}
