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
namespace count_primes {
class Solution {
public:
    static const long LEN = 5 * 1E6;

    int countPrimes(int n) {
        bitset<LEN> arr;
        arr.flip();
        arr[0] = false;
        arr[1] = false;
        int count = 0;
        for (int i = 2; i * i < n; i++) {
            if (!arr[i]) {
                continue;
            }
            int j = i * i;
            while (j < n) {
                arr[j] = false;
                j += i;
            }
        }
        for (int i = 2; i < n; i++) {
            count += arr[i];
        }
        return count;
    }
};
}

void TestForCountPrimes() {
    auto* obj = new count_primes::Solution();
    auto res = obj->countPrimes(499979);
    printf("%d\n", res);
}
