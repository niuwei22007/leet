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
class Solution1 {
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

class Solution2 {
public:
    int ladderLength_BFS(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.count(endWord) == 0) {
            return 0;
        }
        if (beginWord == endWord) {
            return 1;
        }
        queue<string> q;
        q.push(beginWord);
        int step = 0;
        while (!q.empty()) {
            step++;
            int tmpSize = q.size();
            for (int k = 0; k < tmpSize; k++) {
                string tmp = q.front();
                q.pop();
                for (auto &c : tmp) {
                    char tc = c;
                    for (char i = 'a'; i <= 'z'; i++) {
                        c = i;
                        if (tmp == endWord) {
                            return step + 1;
                        }
                        if (wordSet.count(tmp) == 0) {
                            continue;
                        }
                        wordSet.erase(tmp);
                        q.push(tmp);
                    }
                    c = tc;
                }
            }
        }
        return 0;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.count(endWord) == 0) {
            return 0;
        }
        if (beginWord == endWord) {
            return 1;
        }
        unordered_set<string> bq;
        bq.insert(beginWord);

        unordered_set<string> eq;
        eq.insert(endWord);
        int step = 0;

        while (!bq.empty() && !eq.empty()) {
            step++;
            unordered_set<string> tmp;
            if (bq.size() > eq.size()) {
                swap(bq, eq);
            }
            for (auto bw : bq) {
                for (char &c : bw) {
                    char tc = c;
                    for (char i = 'a'; i <= 'z'; i++) {
                        c = i;
                        if (eq.count(bw) > 0) {
                            return step + 1;
                        }
                        if (wordSet.count(bw) == 0) {
                            continue;
                        }
                        wordSet.erase(bw);
                        tmp.insert(bw);
                    }
                    c = tc;
                }
            }
            swap(tmp, bq);
        }
        return 0;
    }
};

class Solution {
    unordered_map<string, int> wordMap_;
    vector<unordered_map<int, bool>> edges_;
    int wordId_{0};
public:
    int PutWord(string &word) {
        if (wordMap_.count(word) == 0) {
            wordMap_[word] = wordId_;
            edges_.emplace_back();
            return wordId_++;
        }
        return wordMap_[word];
    }

    void ExpandWord(string &word) {
        int id1 = PutWord(word);
        for (auto &c:word) {
            char tmp = c;
            c = '*';
            int id2 = PutWord(word);
            edges_[id1][id2] = false;
            edges_[id2][id1] = false;
            c = tmp;
        }
    }

    int ladderLength_BFS(string beginWord, string endWord, vector<string> &wordList) {
        for (auto &word : wordList) {
            ExpandWord(word);
        }
        if (wordMap_.count(endWord) == 0) {
            return 0;
        }
        ExpandWord(beginWord);
        int bid = wordMap_[beginWord];
        int eid = wordMap_[endWord];
        queue<int> q;
        q.push(bid);
        int step = 0;
        while (!q.empty()) {
            ++step;
            int tmpSize = q.size();
            for (int i = 0; i < tmpSize; i++) {
                int tmpId = q.front();
                q.pop();
                for (auto &id : edges_[tmpId]) {
                    if (id.second) {
                        continue;
                    }
                    id.second = true;
                    if (id.first == eid) {
                        return step / 2 + 1;
                    }
                    q.push(id.first);
                }
            }
        }
        return 0;
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        for (auto &word : wordList) {
            ExpandWord(word);
        }
        if (wordMap_.count(endWord) == 0) {
            return 0;
        }
        ExpandWord(beginWord);
        int bid = wordMap_[beginWord];
        int eid = wordMap_[endWord];
        unordered_set<int> bq;
        bq.insert(bid);

        unordered_set<int> eq;
        eq.insert(eid);

        int step = 0;
        while (!bq.empty() && !eq.empty()) {
            ++step;
            if (bq.size() > eq.size()) {
                swap(bq, eq);
            }
            unordered_set<int> tmp;
            for (auto tmpId : bq) {
                for (auto &id : edges_[tmpId]) {
                    if (id.second) {
                        continue;
                    }
                    id.second = true;
                    if (eq.count(id.first) > 0) {
                        return step / 2 + 1;
                    }
                    tmp.insert(id.first);
                }
            }
            swap(bq, tmp);
        }
        return 0;
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
