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
namespace open_lock {
class Solution {
    static const int LEN = 4;

    static inline void Add(string& tmp, int index) {
        if (tmp[index] == '9') {
            tmp[index] = '0';
        } else {
            tmp[index]++;
        }
    }

    static inline void Sub(string& tmp, int index) {
        if (tmp[index] == '0') {
            tmp[index] = '9';
        } else {
            tmp[index]--;
        }
    }

    void BFS(unordered_set<string>& deadSet,
             unordered_set<string>& allSet,
             unordered_set<string>& nextSet,
             int& depth,
             string& target) {
        if (nextSet.empty()) {
            depth = -1;
            return;
        }
        allSet.insert(nextSet.begin(), nextSet.end());
        unordered_set<string> tmpSet;
        depth++;
        for (const string& next:nextSet) {
            string tmpNext = next;
            for (int i = 0; i < LEN; i++) {
                char old = tmpNext[i];
                Add(tmpNext, i);
                if (tmpNext == target) {
                    return;
                }
                if (deadSet.count(tmpNext) == 0) {
                    tmpSet.insert(tmpNext);
                }
                tmpNext[i] = old;

                Sub(tmpNext, i);
                if (tmpNext == target) {
                    return;
                }
                if (deadSet.count(tmpNext) == 0) {
                    tmpSet.insert(tmpNext);
                }
                tmpNext[i] = old;
            }
        }

        BFS(deadSet, allSet, tmpSet, depth, target);
    }

public:
    int openLock(vector<string>& deadends, string target) {
        string start = "0000";
        if (start == target) {
            return 0;
        }
        unordered_set<string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count(start) > 0) {
            return -1;
        }

        int findCount = 0;
        for (int i = 0; i < LEN; i++) {
            char old = target[i];
            Add(target, i);
            findCount += deadSet.count(target);
            target[i] = old;

            Sub(target, i);
            findCount += deadSet.count(target);
            target[i] = old;
        }
        if (findCount == LEN * 2) {
            return -1;
        }

        unordered_set<string> allSet;
        unordered_set<string> nextSet;
        nextSet.insert(start);

        int depth = 0;
        BFS(deadSet, allSet, nextSet, depth, target);
        return depth;
    }
};
}

void TestForOpenLock() {
    auto* obj = new open_lock::Solution();
    string target = "8888";
    vector<string> deadends{"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    auto res = obj->openLock(deadends, target);
    printf("%d\n", res);
}
