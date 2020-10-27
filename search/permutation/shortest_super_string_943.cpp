//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
namespace shortest_superstring {
class Solution1 {
    int N_;
    int bestLength_;
    vector<int> bestPath_;
    vector<vector<int>> minLength_;
public:
    static int Overlap(string &si, string &sj) {
        int minLen = min(si.size(), sj.size());
        for (int i = minLen - 1; i > 0; i--) {
            if (si.substr(si.size() - i) == sj.substr(0, i)) {
                return sj.length() - i;
            }
        }
        return sj.length();
    }

    void InitMinLength(vector<string> &A) {
        minLength_ = vector<vector<int>>(N_, vector<int>(N_));
        for (int i = 0; i < N_; ++i) {
            for (int j = i + 1; j < N_; ++j) {
                minLength_[i][j] = Overlap(A[i], A[j]);
                minLength_[j][i] = Overlap(A[j], A[i]);
            }
        }
    }

    void DFS(vector<string> &A, int depth, int used, int curLen, vector<int> &curPath) {
        if (curLen >= bestLength_) {
            return;
        }
        if (depth >= N_) {
            bestLength_ = curLen;
            bestPath_ = curPath;
            return;
        }
        for (int i = 0; i < N_; i++) {
            if (used & (1 << i)) {
                continue;
            }
            curPath[depth] = i;
            DFS(A,
                depth + 1,
                used | (1 << i),
                depth == 0 ? A[i].size() : curLen + minLength_[curPath[depth - 1]][i],
                curPath);
        }
    }

    string ShortestWithDFS(vector<string> &A) {
        bestLength_ = INT_MAX;
        bestPath_ = vector<int>(N_);
        vector<int> curPath(N_);
        int used = 0;
        DFS(A, 0, used, 0, curPath);

        string ans = A[bestPath_[0]];
        for (int i = 1; i < bestPath_.size(); ++i) {
            int pre = bestPath_[i - 1];
            int next = bestPath_[i];
            ans += A[next].substr(A[next].size() - minLength_[pre][next]);
        }
        return ans;
    }

    string ShortestWithDP(vector<string> &A) {
        vector<vector<int>> dp(1 << N_, vector<int>(N_, INT_MAX / 2));
        vector<vector<int>> path(1 << N_, vector<int>(N_, -1));
        for (int i = 0; i < N_; i++) {
            dp[1 << i][i] = A[i].size();
        }
        // emun each state
        for (int s = 1; s < (1 << N_); s++) {
            for (int i = 0; i < N_; i++) {
                if ((s & (1 << i)) == 0) {
                    continue;
                }
                int prev = s - (1 << i);
                for (int j = 0; j < N_; j++) {
                    if (j == i || (s & (1 << j)) == 0) {
                        continue;
                    }
                    if (dp[prev][j] + minLength_[j][i] < dp[s][i]) {
                        dp[s][i] = dp[prev][j] + minLength_[j][i];
                        path[s][i] = j;
                    }
                }
            }
        }

        int cur = min_element(begin(dp.back()), end(dp.back())) - begin(dp.back());
        int s = (1 << N_) - 1;
        string ans;
        while(s) {
            int prev = path[s][cur];
            if (prev < 0) {
                ans = A[cur] + ans;
            } else {
                ans = A[cur].substr(A[cur].size() - minLength_[prev][cur]) + ans;
            }
            s &= ~(1 << cur);
            cur = prev;
        }

        return ans;
    }

    string shortestSuperstring(vector<string> &A) {
        if (A.empty()) {
            return "";
        }
        if (A.size() == 1) {
            return A[0];
        }
        N_ = A.size();
        InitMinLength(A);
        return ShortestWithDP(A);
    }
};

class Solution {
    vector<vector<int>> dp_;
    vector<vector<int>> path_;
    vector<vector<int>> w_;
    vector<int> bestPath_;
    int bestLength_;
public:
    int Overlap(string &si, string &sj) {
        for (int i = min(si.size(), sj.size()) - 1; i > 0; i--) {
            if (si.substr(si.size() - i) == sj.substr(0, i)) {
                return sj.size() - i;
            }
        }
        return sj.size();
    }

    void DFS(vector<string> &A, int depth, int used, int curLength, vector<int> &curPath) {
        if (curLength >= bestLength_) {
            return;
        }
        if (depth >= A.size()) {
            bestLength_ = curLength;
            bestPath_ = curPath;
            return;
        }
        for (int i = 0; i < A.size(); i++) {
            if (used & (1 << i)) {
                continue;
            }
            curPath[depth] = i;
            DFS(A,
                depth + 1,
                used | (1 << i),
                depth == 0 ? A[i].size() : curLength + w_[curPath[depth - 1]][i],
                curPath
            );
        }
    }

    string shortestSuperstringDFS(vector<string> &A) {
        if (A.empty()) {
            return "";
        }
        if (A.size() == 1) {
            return A[0];
        }
        const int N = A.size();
        w_ = vector<vector<int>>(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; j++) {
                w_[i][j] = Overlap(A[i], A[j]);
                w_[j][i] = Overlap(A[j], A[i]);
            }
        }

        // DO  DFS
        bestLength_ = INT_MAX;
        bestPath_ = vector<int>(N);
        vector<int> curPath(N, -1);
        DFS(A, 0, 0, 0, curPath);

        // backtrack
        string ans = A[bestPath_[0]];
        for (int i = 1; i < bestPath_.size(); ++i) {
            int prev = bestPath_[i - 1];
            int next = bestPath_[i];
            ans += A[next].substr(A[next].size() - w_[prev][next]);
        }
        return ans;
    }

    string shortestSuperstring(vector<string> &A) {
        if (A.empty()) {
            return "";
        }
        if (A.size() == 1) {
            return A[0];
        }
        const int N = A.size();
        const int M = 1 << N;
        w_ = vector<vector<int>>(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; j++) {
                w_[i][j] = Overlap(A[i], A[j]);
                w_[j][i] = Overlap(A[j], A[i]);
            }
        }

        // DO DP
        dp_ = vector<vector<int>>(M, vector<int>(N, INT_MAX / 2));
        path_ = vector<vector<int>>(M, vector<int>(N, -1));

        // init dp array
        for (int i = 0; i < N; i++) {
            dp_[1 << i][i] = A[i].size();
        }

        // transaction
        for (int k = 0; k < M; k++) {
            for (int i = 0; i < N; ++i) {
                if ((k & (1 << i)) == 0) {
                    continue;
                }
//                int kjj = k & (~(1 << i));
                int kj = k - (1 << i);
//                printf("kjj:%d, kj:%d\n", kjj, kj);
                for (int j = 0; j < N; ++j) {
                    if (j == i || (k & (1 << j)) == 0) {
                        continue;
                    }
                    // do trans
                    if ((dp_[kj][j] + w_[j][i]) < dp_[k][i]) {
                        dp_[k][i] = dp_[kj][j] + w_[j][i];
                        path_[k][i] = j;
                    }
                }
            }
        }

        // backtrack
        auto best = dp_.back();
        int current = min_element(best.begin(), best.end()) - best.begin();
        int index = N - 1;
        int states = M - 1;
        bestPath_ = vector<int>(N);
        bestPath_[index] = current;
        while (index > 0) {
            int prev = path_[states][current];
            bestPath_[--index] = prev;
            states -= (1 << current);
            current = prev;
        }
        string ans = A[bestPath_[0]];
        for (int i = 1; i < bestPath_.size(); ++i) {
            int prev = bestPath_[i - 1];
            int next = bestPath_[i];
            ans += A[next].substr(A[next].size() - w_[prev][next]);
        }
        return ans;
    }
};
}

void TestForShortesSuperString() {
    auto *obj = new shortest_superstring::Solution();
//    vector<string> strs{"catg", "ctaagt", "gcta", "ttca", "atgcatc"};
    vector<string> strs{"alex","loves","leetcode"};
    auto result = obj->shortestSuperstring(strs);
    printf("%s\n", result.c_str());
}
