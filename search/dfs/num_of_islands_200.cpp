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
namespace num_of_islands {
class Solution {
    void DFS(vector<vector<char>>& grid, int r, int c) {
        if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] > '0') {
            grid[r][c] = '0';
            DFS(grid, r + 1, c);
            DFS(grid, r - 1, c);
            DFS(grid, r, c + 1);
            DFS(grid, r, c - 1);
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    DFS(grid, i, j);
                }
            }
        }
        return count;
    }
};
}

void TestForNumOfIslands() {
    auto* obj = new num_of_islands::Solution();

    vector<vector<char>> board = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'},
    };
    auto res = obj->numIslands(board);
    printf("%d", res);
}
