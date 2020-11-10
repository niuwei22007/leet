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
                if (deadSet.count(tmpNext) == 0 && allSet.count(tmpNext) == 0) {
                    tmpSet.insert(tmpNext);
                }
                tmpNext[i] = old;

                Sub(tmpNext, i);
                if (tmpNext == target) {
                    return;
                }
                if (deadSet.count(tmpNext) == 0 && allSet.count(tmpNext) == 0) {
                    tmpSet.insert(tmpNext);
                }
                tmpNext[i] = old;
            }
        }

        BFS(deadSet, allSet, tmpSet, depth, target);
    }

    void BiBFS(unordered_set<string>& deadSet,
               unordered_set<string>& allSet,
               unordered_set<string>& leftSet,
               unordered_set<string>& rightSet,
               int& depth) {
        if (leftSet.empty()) {
            depth = -1;
            return;
        }
        if (leftSet.size() > rightSet.size()) {
            swap(leftSet, rightSet);
        }

        depth++;
        unordered_set<string> tmpSet;
        allSet.insert(leftSet.begin(), leftSet.end());
        for (const string& next: leftSet) {
            string tmp = next;
            for (int i = 0; i < LEN; i++) {
                char old = tmp[i];
                Add(tmp, i);
                if (rightSet.count(tmp) > 0) {
                    return;
                }
                if (deadSet.count(tmp) == 0 && allSet.count(tmp) == 0) {
                    tmpSet.insert(tmp);
                }
                tmp[i] = old;

                Sub(tmp, i);
                if (rightSet.count(tmp) > 0) {
                    return;
                }
                if (deadSet.count(tmp) == 0 && allSet.count(tmp) == 0) {
                    tmpSet.insert(tmp);
                }
                tmp[i] = old;
            }
        }
        BiBFS(deadSet, allSet, tmpSet, rightSet, depth);
    }

public:
    int openLock_BFS(vector<string>& deadends, string target) {
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
        unordered_set<string> leftSet;
        unordered_set<string> rightSet;
        leftSet.insert(start);
        rightSet.insert(target);

        int depth = 0;
        BiBFS(deadSet, allSet, leftSet, rightSet, depth);
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
