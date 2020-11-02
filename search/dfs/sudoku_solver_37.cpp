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
#include <unordered_set>
#include <unordered_map>

using namespace std;
namespace sudoku_solver {
class Solution {
    bool rows_[9][9] = {false};
    bool cols_[9][9] = {false};
    bool grid_[3][3][9] = {false};
    bool isFind_ = false;
    vector<pair<int, int>> space_;
public:

    void DFS(vector<vector<char>> &board, int index) {
        if (index == space_.size()) {
            isFind_ = true;
            return;
        }
        int r = space_[index].first;
        int l = space_[index].second;
        for (int d = 0; d < 9; d++) {
            if (isFind_) {
                return;
            }
            if (!rows_[r][d] && !cols_[l][d] && !grid_[r / 3][l / 3][d]) {
                rows_[r][d] = true;
                cols_[l][d] = true;
                grid_[r / 3][l / 3][d] = true;
                board[r][l] = d + '1';
                DFS(board, index + 1);
                rows_[r][d] = false;
                cols_[l][d] = false;
                grid_[r / 3][l / 3][d] = false;
            }
        }
    }

    void solveSudoku(vector<vector<char>> &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    space_.emplace_back(i, j);
                } else {
                    int d = board[i][j] - '1';
                    rows_[i][d] = true;
                    cols_[j][d] = true;
                    grid_[i / 3][j / 3][d] = true;
                }
            }
        }
        DFS(board, 0);
    }
};
}

void TestForSudokuSolver() {
    auto *obj = new sudoku_solver::Solution();
    char tmp[9][9] = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    vector<vector<char>> board(9, vector<char>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = tmp[i][j];
        }
    }
    obj->solveSudoku(board);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c\t", board[i][j]);
        }
        printf("\n");
    }
}
