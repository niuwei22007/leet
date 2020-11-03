//
// Created by 鞋底洞 on 2020/10/19.
//
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

using namespace std;
namespace queens_solver {
class Solution {
    static const int N = 1000;
    vector<vector<string>> ans_;
public:
    static bool CheckSlope(vector<bitset<N>> &rows, vector<bitset<N>> &cols, int i, int j) {
        // 往左上斜
        for (int m = i, n = j; m >= 0 && n < rows.size(); m--, n++) {
            if (rows[m][n]) {
                return false;
            }
        }
        // 往右上斜
        for (int m = i, n = j; m >= 0 && n >= 0; m--, n--) {
            if (rows[m][n]) {
                return false;
            }
        }
        return true;
    }

    static vector<pair<int, int>> GetNext(vector<bitset<N>> &rows, vector<bitset<N>> &cols) {
        vector<pair<int, int>> next;
        for (int i = 0; i < rows.size(); i++) {
            // 横向不能有1
            if (rows[i].count() > 0) {
                continue;
            }
            for (int j = 0; j < cols.size(); j++) {
                // 纵向不能有1
                if (cols[j].count() > 0) {
                    continue;
                }
                // 斜对角线也不能有1
                if (!CheckSlope(rows, cols, i, j)) {
                    continue;
                }
                next.emplace_back(i, j);
            }
            if (!next.empty()) {
                return next;
            }
        }
        return next;
    }

    static void
    PutQueen(vector<string> &tmp, vector<bitset<N>> &rows, vector<bitset<N>> &cols, int i, int j, bool label) {
        rows[i].set(j, label);
        cols[j].set(i, label);
        tmp[i][j] = label ? 'Q' : '.';
    }


    void DFS(vector<string> &tmp, vector<bitset<N>> &rows, vector<bitset<N>> &cols, int target) {
        if (target == 0) {
            ans_.push_back(tmp);
            return;
        }
        auto next = GetNext(rows, cols);
        if (!next.empty()) {
            for (auto coordinate: next) {
                int r = coordinate.first;
                int c = coordinate.second;
                PutQueen(tmp, rows, cols, r, c, true);
                DFS(tmp, rows, cols, target - 1);
                PutQueen(tmp, rows, cols, r, c, false);
            }
        }
    }


    vector<vector<string>> solveNQueens(int n) {
        vector<bitset<N>> rows(n, bitset<N>(0));
        vector<bitset<N>> cols(n, bitset<N>(0));
        string rowStr;
        for (int i = 0; i < n; i++) {
            rowStr.append(".");
        }
        vector<string> tmp;
        tmp.reserve(n);
        for (int i = 0; i < n; i++) {
            tmp.push_back(rowStr);
        }
        DFS(tmp, rows, cols, n);
        return ans_;
    }
};

}

void TestForQueenSolver() {
    auto *obj = new queens_solver::Solution();
    auto result = obj->solveNQueens(4);
    for (auto &s : result) {
        for (auto &c:s) {
            printf("%s\n", c.c_str());
        }
        printf("\n");
    }
    printf("---- %d\n", result.size());
}
