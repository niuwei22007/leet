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
namespace search_word {
class Solution {
public:
    static bool
    DFS(vector<vector<char>> &board, int row, int col, vector<vector<bool>> &used, string &word, int index) {
        if (index == word.size()) {
            return true;
        }
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
            used[row][col] || word[index] != board[row][col]) {
            return false;
        }
        used[row][col] = true;
        // up
        if (DFS(board, row - 1, col, used, word, index + 1)) {
            return true;
        }
        // down
        if (DFS(board, row + 1, col, used, word, index + 1)) {
            return true;
        }
        // left
        if (DFS(board, row, col - 1, used, word, index + 1)) {
            return true;
        }
        // right
        if (DFS(board, row, col + 1, used, word, index + 1)) {
            return true;
        }

        used[row][col] = false;
        return false;
    }

    bool exist(vector<vector<char>> &board, string word) {
        if (word.size() > board.size() * board[0].size()) {
            return false;
        }
        vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (DFS(board, i, j, used, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};
}

void TestForSearchWord() {
    auto *obj = new search_word::Solution();
    vector<vector<char>> board{
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}
    };
    auto result = obj->exist(board, "ABCB");
    printf("---- %d\n", result);
}
