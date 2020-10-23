//
// Created by 鞋底洞 on 2020/10/22.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;
namespace nextlarger {

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
    stack<pair<int, int>> incStack_;
public:
    vector<int> nextLargerNodes(ListNode *head) {
        vector<int> result;
        auto tmp = head;
        int count = 0;
        while (tmp != nullptr) {
            result.push_back(0);
            while (!incStack_.empty() && incStack_.top().first < tmp->val) {
                result[incStack_.top().second] = tmp->val;
                incStack_.pop();
            }
            incStack_.push(make_pair(tmp->val, count++));
            tmp = tmp->next;
        }
        return result;
    }
};
}

void TestForNextLarger() {
    auto *obj = new nextlarger::Solution();
    vector<int> subarray = {1,7,5,1,9,2,5,1};
    auto *head = new nextlarger::ListNode(subarray[0]);
    auto *tmp = head;
    for (int i = 1; i < subarray.size(); ++i) {
        tmp->next = new nextlarger::ListNode(subarray[i]);
        tmp = tmp->next;
    }
    auto res = obj->nextLargerNodes(head);
    for (auto r: res) {
        printf("%d ", r);
    }
}
