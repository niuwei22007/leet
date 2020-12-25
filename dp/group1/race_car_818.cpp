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
namespace race_car {
class Solution {
public:
    struct Node {
        long location;
        long speed;

        Node(long loc, long sp) {
            location = loc;
            speed = sp;
        }
    };

    struct NodeHash {
        size_t operator()(const Node& n) const {
            return hash<long>()(n.location) ^ hash<long>()(n.speed);
        }
    };

    struct NodeCmp {
        bool operator()(const Node& a, const Node& b) const {
            return a.location == b.location && a.speed == b.speed;
        }
    };

    int racecar(int target) {
        queue<Node> q;
        unordered_set<Node, NodeHash, NodeCmp> visited;
        q.push(Node(0, 1));
        visited.insert(q.front());
        int step = 0;
        while (!q.empty()) {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto cur = q.front();
                q.pop();
                // A
                auto moveA = Node(cur.location + cur.speed, cur.speed * 2);
                if (moveA.location == target) {
                    return step;
                }
                if (visited.find(moveA) == visited.end()) {
                    visited.insert(moveA);
                    q.push(moveA);
                }
                // R
                auto moveR = Node(cur.location, cur.speed > 0 ? -1 : 1);
                if (moveR.location == target) {
                    return step;
                }
                if (visited.find(moveR) == visited.end()) {
                    visited.insert(moveR);
                    q.push(moveR);
                }
            }
        }
        return -1;
    }
};
}

void TestForRaceCar() {
    auto* obj = new race_car::Solution();
    auto res = obj->racecar(5438);
    printf("%d\n", res);
}
