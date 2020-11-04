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
namespace queens_solver2 {
class Solution {
    static const int MAX_LEN = 100;
    vector<bitset<MAX_LEN>> bone_;
public:
    bool Check(int row, int col) {
        // 列不能有
        for (int i = 0; i < row; i++) {
            if (bone_[i][col]) {
                return false;
            }
        }
        // 左上斜
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (bone_[i][j]) {
                return false;
            }
        }
        // 右上斜
        for (int i = row, j = col; i >= 0 && j < bone_.size(); i--, j++) {
            if (bone_[i][j]) {
                return false;
            }
        }
        return true;
    }

    void DFS(int target, int row, int &result) {
        if (row == target) {
            result++;
            return;
        }
        for (int i = 0; i < target; i++) {
            if (Check(row, i)) {
                bone_[row].set(i, true);
                DFS(target, row + 1, result);
                bone_[row].set(i, false);
            }
        }
    }

    int totalNQueens(int n) {
        if (n <= 3) {
            return 0;
        }
        bone_ = vector<bitset<MAX_LEN>>(n, bitset<MAX_LEN>(0));
        int result = 0;
        DFS(n, 0, result);
        return result;
    }
};

}

void TestForQueenSolver2() {
    auto *obj = new queens_solver2::Solution();
    auto result = obj->totalNQueens(8);
    printf("---- %d\n", result);
}
