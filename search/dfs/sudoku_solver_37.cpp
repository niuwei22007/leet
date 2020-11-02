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
namespace sudoku_solver {
class Solution {
    vector<bitset<9>> rows_;
    vector<bitset<9>> cols_;
    vector<vector<bitset<9>>> ceils_;
public:

    void FillDigit(int i, int j, int digit, bool isSet) {
        rows_[i].set(digit, isSet);
        cols_[j].set(digit, isSet);
        ceils_[i / 3][j / 3].set(digit, isSet);
    }

    pair<pair<int, int>, bitset<9>> GetNext(vector<vector<char>> &board) {
        int bestRow = 0, bestCol = 0;
        bitset<9> bestValue(0);
        bitset<9> tmp;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') {
                    continue;
                }
                tmp = rows_[i] | cols_[j] | ceils_[i / 3][j / 3];
                if (tmp.count() > bestValue.count()) {
                    bestValue = tmp;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
        return make_pair(make_pair(bestRow, bestCol), bestValue);
    }

    bool DFS(vector<vector<char>> &board, int empty) {
        if (empty == 0) {
            return true;
        }
        auto next = GetNext(board);
        int row = next.first.first;
        int col = next.first.second;
        bitset<9> value = next.second;

        for (int i = 0; i < 9; i++) {
            if (!value[i]) {
                board[row][col] = i + '1';
                FillDigit(row, col, i, true);
                if (DFS(board, empty - 1)) {
                    return true;
                }
                FillDigit(row, col, i, false);
                board[row][col] = '.';
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>> &board) {
        rows_ = vector<bitset<9>>(9, bitset<9>(0));
        cols_ = vector<bitset<9>>(9, bitset<9>(0));
        ceils_ = vector<vector<bitset<9>>>(3, vector<bitset<9>>(3, bitset<9>(0)));
        int empty = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    empty++;
                } else {
                    int digit = board[i][j] - '1';
                    FillDigit(i, j, digit, true);
                }
            }
        }
        DFS(board, empty);
    }
};

class Solution_Common {
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
