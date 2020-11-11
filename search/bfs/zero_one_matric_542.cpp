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
    vector<vector<int>> updateMatrix_BFS(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return vector<vector<int>>();
        }
        int n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n, 0));
        vector<vector<bool>> used(m, vector<bool>(n, false));

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    q.emplace(i, j);
                    used[i][j] = true;
                }
            }
        }

        while (!q.empty()) {
            auto[i, j] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];

                if (ni < 0 || ni >= m || nj < 0 || nj >= n || used[ni][nj]) {
                    continue;
                }

                dist[ni][nj] = dist[i][j] + 1;
                used[ni][nj] = true;
                q.emplace(ni, nj);
            }
        }
        return dist;
    }

    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i + 1) < m) {
                    dist[i + 1][j] = min(dist[i + 1][j], dist[i][j] + 1);
                }
                if ((j + 1) < n) {
                    dist[i][j + 1] = min(dist[i][j + 1], dist[i][j] + 1);
                }
            }
        }

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if ((i - 1) >= 0) {
                    dist[i - 1][j] = min(dist[i - 1][j], dist[i][j] + 1);
                }
                if ((j - 1) >= 0) {
                    dist[i][j - 1] = min(dist[i][j - 1], dist[i][j] + 1);
                }
            }
        }

        return dist;
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
