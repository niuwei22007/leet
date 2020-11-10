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

    static inline void Change(string& tmp, int index, bool add) {
        if (add) {
            if (tmp[index] == '9') {
                tmp[index] = '0';
            } else {
                tmp[index]++;
            }
        } else {
            if (tmp[index] == '0') {
                tmp[index] = '9';
            } else {
                tmp[index]--;
            }
        }
    }

    void DFS(unordered_map<string, vector<string>>& path,
             vector<vector<string>>& res,
             vector<string>& tmp,
             string& next,
             string& target) {
        if (next == target) {
            res.push_back(tmp);
            return;
        }
        if (path.count(next) == 0 || path[next].empty()) {
            return;
        }

        for (string& n : path[next]) {
            tmp.push_back(n);
            DFS(path, res, tmp, n, target);
            tmp.pop_back();
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
               unordered_map<string, vector<string>>& path,
               int& depth,
               bool reverse) {
        if (leftSet.empty()) {
            depth = -1;
            return;
        }
        if (leftSet.size() > rightSet.size()) {
            swap(leftSet, rightSet);
            reverse = !reverse;
        }

        depth++;
        unordered_set<string> tmpSet;
        allSet.insert(leftSet.begin(), leftSet.end());
        bool isFind = false;
        for (const string& next: leftSet) {
            string tmp = next;
            for (int i = 0; i < LEN; i++) {
                for (int j = 0; j < 2; j++) {
                    char old = tmp[i];
                    Change(tmp, i, j);
                    if (rightSet.count(tmp) > 0) {
                        isFind = true;
                    }
                    if (deadSet.count(tmp) == 0 && allSet.count(tmp) == 0) {
                        tmpSet.insert(tmp);
                        string key = reverse ? tmp : next;
                        string val = reverse ? next : tmp;
                        if (path.count(key) == 0) {
                            path[key] = vector<string>();
                        }
                        path[key].push_back(val);
                    }
                    tmp[i] = old;
                }
            }
        }
        if (!isFind) {
            BiBFS(deadSet, allSet, tmpSet, rightSet, path, depth, reverse);
        }
    }

    void ShowPath(vector<vector<string>>& res) {
        for (const vector<string>& p : res) {
            for (const string& n : p) {
                printf("%s --> ", n.c_str());
            }
            printf("\n");
        }
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
        unordered_map<string, vector<string>> path;
        leftSet.insert(start);
        rightSet.insert(target);

        int depth = 0;
        BiBFS(deadSet, allSet, leftSet, rightSet, path, depth, false);

        vector<vector<string>> res;
        vector<string> tmp;
        tmp.push_back(start);
        DFS(path, res, tmp, start, target);
        ShowPath(res);
        return depth;
    }
};
}

void TestForOpenLock() {
    auto* obj = new open_lock::Solution();
    string target = "0202";
    vector<string> deadends{"0201", "0101", "0102", "1212", "2002"};
    auto res = obj->openLock(deadends, target);
    printf("%d\n", res);
}
