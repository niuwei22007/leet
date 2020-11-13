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
namespace cutoff_trees {
class Solution {
    using P = tuple<int, int, int>;
    int dirs[4][2] = {{-1, 0},
                      {1,  0},
                      {0,  -1},
                      {0,  1}};
    int minStep = 0;

    int BFS(vector<vector<int>>& forest, int sr, int sc, int tr, int tc) {
        int n = forest.size();
        int m = forest[0].size();
        vector<vector<bool>> used(n, vector<bool>(m, false));
        queue<P> q;
        q.emplace(sr, sc, 0);
        used[sr][sc] = true;
        while (!q.empty()) {
            P s = q.front();
            q.pop();
            if (get<0>(s) == tr && get<1>(s) == tc) {
                return get<2>(s);
            }
            for (auto& dir : dirs) {
                int nr = get<0>(s) + dir[0];
                int nc = get<1>(s) + dir[1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !used[nr][nc] && forest[nr][nc] > 0) {
                    used[nr][nc] = true;
                    q.emplace(nr, nc, get<2>(s) + 1);
                }
            }
        }
        return -1;
    }

public:
    static bool compare(const tuple<int, int, int>& t1, const tuple<int, int, int>& t2) {
        return get<0>(t1) < get<0>(t2); //降序排列
    }

    int cutOffTree(vector<vector<int>>& forest) {
        vector<tuple<int, int, int>> seq;
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[0].size(); j++) {
                if (forest[i][j] > 1) {
                    seq.emplace_back(forest[i][j], i, j);
                }
            }
        }
        sort(seq.begin(), seq.end(), compare);

        int sr = 0, sc = 0;
        for (auto& i : seq) {
            int tr = get<1>(i);
            int tc = get<2>(i);
            int tmpStep = BFS(forest, sr, sc, tr, tc);
            if (tmpStep < 0) {
                return -1;
            }
            minStep += tmpStep;
            sr = tr;
            sc = tc;
        }
        return minStep == 0 ? -1 : minStep;
    }
};
}

void TestForCutOffTrees() {
    auto* obj = new cutoff_trees::Solution();
    vector<vector<int>> forest{
        {54581641, 64080174, 24346381, 69107959},
        {86374198, 61363882, 68783324, 79706116},
        {668150, 92178815, 89819108, 94701471},
        {83920491, 22724204, 46281641, 47531096},
        {89078499, 18904913, 25462145, 60813308}
    };
    auto res = obj->cutOffTree(forest);
    printf("%d\n", res);
}
