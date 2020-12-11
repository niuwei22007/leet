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
namespace split_word {
class Solution {
    static const int LEN = 26;

    class TrieNode {
    public:
        bool isEnd_;
        TrieNode* child_[LEN]{};

        TrieNode() {
            isEnd_ = false;
        }
    };

    TrieNode* root_;
    vector<int> cache_;

    void Add(string& word) {
        TrieNode* tmp = root_;
        for (char w : word) {
            int index = w - 'a';
            if (tmp != nullptr && tmp->child_[index] == nullptr) {
                tmp->child_[index] = new TrieNode();
            }
            tmp = tmp->child_[index];
        }
        tmp->isEnd_ = true;
    }

    bool DFS(string& s, int index) {
        if (index == s.length()) {
            return true;
        }
        if (cache_[index] > -1) {
            return cache_[index];
        }
        TrieNode* tmp = root_;
        for (int i = index; i < s.length(); i++) {
            int wi = s[i] - 'a';
            if (tmp->child_[wi] == nullptr) {
                cache_[i] = false;
                return false;
            }
            if (tmp->child_[wi]->isEnd_) {
                if (DFS(s, i + 1)) {
                    return true;
                }
            }
            tmp = tmp->child_[wi];
        }
        cache_[index] = false;
        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        root_ = new TrieNode();
        cache_ = vector<int>(s.length(), -1);
        for (auto& word : wordDict) {
            Add(word);
        }
        return DFS(s, 0);
    }
};
}

void TestForSplitWord() {
    auto* obj = new split_word::Solution();
    string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    vector<string> dict{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    auto res = obj->wordBreak(s, dict);
    printf("%d\n", res);
}
