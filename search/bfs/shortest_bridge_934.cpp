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
namespace shortet_bridge {
class Solution {
    queue<pair<int, int>> q;
private:
    void DFS(vector<vector<int>>& A, int i, int j) {
        if (i >= 0 && i < A.size() && j >= 0 && j < A.size() && A[i][j] == 1) {
            q.emplace(i, j);
            A[i][j] = 2;
            DFS(A, i + 1, j);
            DFS(A, i - 1, j);
            DFS(A, i, j + 1);
            DFS(A, i, j - 1);
        }
    }

    bool Visit(vector<vector<int>>& A, int i, int j) {
        if (i >= 0 && i < A.size() && j >= 0 && j < A.size()) {
            if (A[i][j] == 0) {
                q.emplace(i, j);
                A[i][j] = 2;
            }
            return A[i][j] == 1;
        }
        return false;
    }

public:
    int shortestBridge(vector<vector<int>>& A) {
        int n = A.size();
        int m = A[0].size();
        int count = 0;
        bool findBridge = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (A[i][j] == 1) {
                    DFS(A, i, j);
                    findBridge = true;
                    break;
                }
            }
            if (findBridge) {
                break;
            }
        }

        while (!q.empty()) {
            int tmpSize = q.size();
            for (int k = 0; k < tmpSize; k++) {
                auto[i, j] = q.front();
                q.pop();
                bool finish = Visit(A, i + 1, j);
                finish |= Visit(A, i - 1, j);
                finish |= Visit(A, i, j + 1);
                finish |= Visit(A, i, j - 1);
                if (finish) {
                    return count;
                }
            }
            count++;
        }
        return count;
    }
};
}

void TestForShortestBridge() {
    auto* obj = new shortet_bridge::Solution();
    vector<vector<int>> matrix{
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
    };
    auto res = obj->shortestBridge(matrix);
    printf("%d", res);
}
