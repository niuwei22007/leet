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
namespace zero_one {
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0},
                                       {1,  0},
                                       {0,  -1},
                                       {0,  1}};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        vector<vector<int>> ans;
        if (matrix.empty()) {
            return ans;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        ans = vector<vector<int>>(m, vector<int>(n));
        vector<vector<int>> used(m, vector<int>(n));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    q.emplace(i, j);
                    used[i][j] = 1;
                }
            }
        }
        while (!q.empty()) {
            pair<int, int>& loc = q.front();
            q.pop();
            int i = loc.first, j = loc.second;
            for (int d = 0; d < 4; d++) {
                int newI = i + dirs[d][0];
                int newJ = j + dirs[d][1];
                if ((newI < 0 || newI >= m || newJ < 0 || newJ >= n || used[newI][newJ] == 1)) {
                    continue;
                }
                ans[newI][newJ] = ans[i][j] + 1;
                q.emplace(newI, newJ);
                used[i][j] = 1;
            }
        }
        return ans;
    }
};
}

void TestForZeroOne() {
    auto* obj = new zero_one::Solution();
    vector<vector<int>> matrix{
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 0, 1, 0, 0, 1, 1}
    };
    auto res = obj->updateMatrix(matrix);
    for (const vector<int>& ma: res) {
        for (const int m : ma) {
            printf("%d ", m);
        }
        printf("\n");
    }
}
