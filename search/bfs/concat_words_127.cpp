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


    int BiBFS(int begin, int end) {
        vector<int> disB(numId_, INT_MAX);
        queue<int> bq;
        bq.push(begin);
        disB[begin] = 0;

        vector<int> disE(numId_, INT_MAX);
        queue<int> eq;
        eq.push(end);
        disE[end] = 0;


        while (!bq.empty() && !eq.empty()) {
            int bqSize = bq.size();
            for (int i = 0; i < bqSize; i++) {
                int bid = bq.front();
                bq.pop();
                if (disE[bid] != INT_MAX) {
                    return (disB[bid] + disE[bid]) / 2 + 1;
                }
                for (auto &bbid : edges_[bid]) {
                    if (disB[bbid] == INT_MAX) {
                        disB[bbid] = disB[bid] + 1;
                        bq.push(bbid);
                    }
                }
            }


            int eqSize = eq.size();
            for (int i = 0; i < eqSize; i++) {
                int eid = eq.front();
                eq.pop();
                if (disB[eid] != INT_MAX) {
                    return (disB[eid] + disE[eid]) / 2 + 1;
                }
                for (auto &eeid : edges_[eid]) {
                    if (disE[eeid] == INT_MAX) {
                        disE[eeid] = disE[eid] + 1;
                        eq.push(eeid);
                    }
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

        return BiBFS(dict_[beginWord], dict_[endWord]);
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
