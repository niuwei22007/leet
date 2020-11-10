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
#include <algorithm>

using namespace std;
namespace concat_word2 {
class Solution {
    void ShowPath(unordered_map<string, vector<string>>& path) {
        for (auto p : path) {
            printf("[nyh] %s: ", p.first.c_str());
            for (auto w:p.second) {
                printf("%s ", w.c_str());
            }
            printf("\n");
        }
    }

    void BFS(unordered_set<string>& wordSet, unordered_set<string>& startSet, string& endWord,
             unordered_map<string, vector<string>>& path) {
        if (startSet.empty()) {
            return;
        }
        for (auto& word:startSet) {
            wordSet.erase(word);
        }
        unordered_set<string> tmpSet;
        bool isFinish = false;
        for (auto word:startSet) {
            string key = word;
            for (char& wc : word) {
                char old = wc;
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == old) {
                        continue;
                    }
                    wc = c;
                    if (wordSet.count(word) == 0) {
                        continue;
                    }

                    if (word == endWord) {
                        isFinish = true;
                    } else {
                        tmpSet.insert(word);
                    }

                    const string& val = word;
                    if (path.count(key) == 0) {
                        path[key] = vector<string>();
                    }
                    path[key].push_back(val);
                }
                wc = old;
            }
        }
        if (!isFinish) {
            BFS(wordSet, tmpSet, endWord, path);
        }
    }

    void BiBFS(unordered_set<string>& wordSet, unordered_set<string>& startSet, unordered_set<string>& endSet,
               unordered_map<string, vector<string>>& path, bool reverse) {
        if (startSet.empty()) {
            return;
        }

        if (startSet.size() > endSet.size()) {
            BiBFS(wordSet, endSet, startSet, path, !reverse);
            return;
        }

        unordered_set<string> tmpSet;
        for (auto& word:startSet) {
            wordSet.erase(word);
        }
        bool isFind = false;
        for (auto& word:startSet) {
            string tmpWord = word;
            for (auto& wc : tmpWord) {
                char old = wc;
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == old) {
                        continue;
                    }
                    wc = c;
                    if (wordSet.count(tmpWord) == 0) {
                        continue;
                    }
                    if (endSet.count(tmpWord) > 0) {
                        isFind = true;
                    } else {
                        tmpSet.insert(tmpWord);
                    }

                    string key = reverse ? tmpWord : word;
                    string val = reverse ? word : tmpWord;
                    if (path.count(key) == 0) {
                        path[key] = vector<string>();
                    }
                    path[key].push_back(val);
                }
                wc = old;
            }
        }
        if (!isFind) {
            BiBFS(wordSet, tmpSet, endSet, path, reverse);
        }
    }

    void DFS(unordered_map<string, vector<string>>& path, string& endWord, vector<string>& tmpPath,
             vector<vector<string>>& res, string& next) {
        if (next == endWord) {
            res.push_back(tmpPath);
            return;
        }

        if (path.count(next) == 0) {
            return;
        }

        for (auto& word : path[next]) {
            tmpPath.push_back(word);
            DFS(path, endWord, tmpPath, res, word);
            tmpPath.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders_BFS(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res;
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.count(endWord) == 0) {
            return res;
        }

        unordered_set<string> startSet;
        startSet.insert(beginWord);

        unordered_map<string, vector<string>> path;
        BFS(wordSet, startSet, endWord, path);
        printf("[==================]");
        ShowPath(path);
        vector<string> tmpPath;
        tmpPath.push_back(beginWord);
        DFS(path, endWord, tmpPath, res, beginWord);

        return res;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res;
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.count(endWord) == 0) {
            return res;
        }

        unordered_set<string> startSet;
        startSet.insert(beginWord);

        unordered_set<string> endSet;
        endSet.insert(endWord);

        unordered_map<string, vector<string>> path;
        BiBFS(wordSet, startSet, endSet, path, false);
        printf("[==================]\n");
        ShowPath(path);
        vector<string> tmpPath;
        tmpPath.push_back(beginWord);
        DFS(path, endWord, tmpPath, res, beginWord);

        return res;
    }
};
}

void TestForConcatWords2() {
    auto* obj = new concat_word2::Solution();
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
    auto res = obj->findLadders(beginWord, endWord, wordList);
    // res = obj->findLadders_BFS(beginWord, endWord, wordList);
    for (auto& wordSet : res) {
        for (auto& word : wordSet) {
            printf("%s ", word.c_str());
        }
        printf("\n");
    }
}
