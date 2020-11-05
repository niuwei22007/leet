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
namespace concat_word {
class Solution {
    unordered_map<string, int> dict_;
    vector<set<int>> edges_;
    int numId_{0};
public:

    int PutDict(string &word) {
        if (dict_.count(word) == 0) {
            dict_[word] = numId_;
            edges_.emplace_back();
            return numId_++;
        }
        return dict_[word];
    }

    void AddEdge(string &word) {
        int id1 = PutDict(word);
        for (auto &c : word) {
            char tmp = c;
            c = '*';
            int id2 = PutDict(word);
            edges_[id1].insert(id2);
            edges_[id2].insert(id1);
            c = tmp;
        }
    }

    int BFS(int begin, int end) {
        queue<int> q;
        q.push(begin);
        vector<int> dis(numId_, INT_MAX);
        dis[begin] = 0;
        while (!q.empty()) {
            int id = q.front();
            q.pop();

            if (id == end) {
                return dis[end] / 2 + 1;
            }
            for (auto &i : edges_[id]) {
                if (dis[i] == INT_MAX) {
                    dis[i] = dis[id] + 1;
                    q.push(i);
                }
            }
        }
        return 0;
    }


    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        if (wordList.empty()) {
            return 0;
        }
        for (auto &word:wordList) {
            AddEdge(word);
        }
        AddEdge(beginWord);
        if (dict_.count(endWord) == 0) {
            return 0;
        }
        AddEdge(endWord);

        return BFS(dict_[beginWord], dict_[endWord]);
    }
};
}

void TestForConcatWords() {
    auto *obj = new concat_word::Solution();
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
    auto res = obj->ladderLength(beginWord, endWord, wordList);
    printf("%d\n", res);
}
