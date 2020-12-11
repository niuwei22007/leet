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
    vector<int> cache_;
    vector<string> memory_;

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

    void DFS(string& s, int index, vector<string>& res, string& tmp) {
        if (index == s.length()) {
            res.push_back(tmp);
            return;
        }
        TrieNode* next = root_;
        for (int i = index; i < s.length(); i++) {
            int wi = s[i] - 'a';
            if (next->child_[wi] == nullptr) {
                return;
            }
            if (!next->child_[wi]->value_.empty()) {
                int oldSize = tmp.size();
                tmp += (tmp.empty() ? "" : " ") + next->child_[wi]->value_;
                DFS(s, i + 1, res, tmp);
                tmp.resize(oldSize);
            }
            next = next->child_[wi];
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        root_ = new TrieNode();
        cache_ = vector<int>(s.length() + 1, -1);
        memory_ = vector<string>(s.length() + 1);
        for (auto& word : wordDict) {
            Add(word);
        }
        vector<string> res;
        string tmp;
        DFS(s, 0, res, tmp);
        return res;
    }
};
}

void TestForSplitWord2() {
    auto* obj = new split_word2::Solution();
    string s = "catsanddog";
    vector<string> dict{"cat", "cats", "and", "sand", "dog"};
    auto res = obj->wordBreak(s, dict);
    for (auto& list : res) {
        printf("%s\n", list.c_str());
    }
}
