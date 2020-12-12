#include "../trust.h"
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
namespace split_word2 {
class Solution {
    static const int LEN = 26;

    class TrieNode {
    public:
        string value_;
        TrieNode* child_[LEN]{};

        TrieNode() = default;
    };

    TrieNode* root_;
    unordered_map<int, vector<string>> memory_;

    void Add(string& word) {
        TrieNode* tmp = root_;
        for (char w : word) {
            int index = w - 'a';
            if (tmp != nullptr && tmp->child_[index] == nullptr) {
                tmp->child_[index] = new TrieNode();
            }
            tmp = tmp->child_[index];
        }
        tmp->value_ = word;
    }

    vector<string> DFS(string& s, int index) {
        if (memory_.find(index) != memory_.end()) {
            return memory_[index];
        }

        TrieNode* next = root_;
        vector<string> res;
        for (int i = index; i < s.length(); i++) {
            int wi = s[i] - 'a';
            if (next->child_[wi] == nullptr) {
                break;
            }
            if (!next->child_[wi]->value_.empty()) {
                if (i == s.length() - 1) {
                    res.push_back(next->child_[wi]->value_);
                    break;
                }
                auto rightList = DFS(s, i + 1);
                for (auto& tmp : rightList) {
                    res.push_back(next->child_[wi]->value_ + " " + tmp);
                }
            }
            next = next->child_[wi];
        }
        memory_[index] = res;
        return res;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        root_ = new TrieNode();
        for (auto& word : wordDict) {
            Add(word);
        }
        vector<string> res;
        DFS(s, 0);
        return memory_[0];
    }
};

class Solution_DF_DFS {
public:
    struct TrieNode {
        bool flag;
        map<char, TrieNode*> next;

        TrieNode() : flag(false) {
        }
    };

    TrieNode* root;

    void init(const vector<string>& words) {
        root = new TrieNode;
        for (auto& w : words) {
            auto node = root;
            for (auto c : w) {
                if (!node->next.count(c)) {
                    node->next[c] = new TrieNode;
                }
                node = node->next[c];
            }
            node->flag = true;
        }
    }

    void dfs(const string& s, const vector<vector<int> >& dp, int i, vector<string>& v, vector<string>& res) {
        if (i == 0) {
            string t;
            for (auto it = v.rbegin(); it != v.rend(); ++it) {
                t += *it + " ";
            }
            t.pop_back();
            res.push_back(t);
            return;
        }
        for (auto j : dp[i]) {
            v.push_back(s.substr(j, i - j));
            dfs(s, dp, j, v, res);
            v.pop_back();
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // 构建字典树
        init(wordDict);
        unordered_set<char> cs;
        for (auto& w : wordDict) {
            for (auto c : w) {
                cs.insert(c);
            }
        }
        for (auto c : s) {
            if (cs.count(c) == 0) {
                return {};
            }
        }
        // 动态规划部分
        int N = s.size();
        vector<vector<int> > dp(N + 1);
        dp[0] = vector<int>{-1};
        for (int i = 0; i < N; ++i) {
            if (dp[i].empty())
                continue;
            int j = i;
            auto node = root;
            while (j < N && node->next.count(s[j])) {
                node = node->next[s[j++]];
                if (node->flag) {
                    dp[j].push_back(i);
                }
            }
        }
        // 路径回溯构建所有可能的结果字符串
        vector<string> v;
        vector<string> res;
        dfs(s, dp, N, v, res);
        return res;
    }
};
}

void TestForSplitWord2() {
    auto* obj = new split_word2::Solution();
    // string s = "pineapplepenapple";
    // vector<string> dict{"apple", "pen", "applepen", "pine", "pineapple"};
    string s = "aaaaaaa";
    vector<string> dict{"aaaa", "aaa"};
    // string s = "catsanddog";
    // vector<string> dict{"cat", "cats", "and", "sand", "dog"};

    auto res = obj->wordBreak(s, dict);
    for (auto& list : res) {
        printf("%s\n", list.c_str());
    }
}
