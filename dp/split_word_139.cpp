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
        TrieNode* tmp = root_;
        for (int i = index; i < s.length(); i++) {
            int wi = s[i] - 'a';
            if (tmp->child_[wi] == nullptr) {
                return false;
            }
            if (tmp->child_[wi]->isEnd_) {
                if (DFS(s, i + 1)) {
                    return true;
                }
            }
            tmp = tmp->child_[wi];
        }
        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        root_ = new TrieNode();
        for (auto& word : wordDict) {
            Add(word);
        }
        return DFS(s, 0);
    }
};
}

void TestForSplitWord() {
    auto* obj = new split_word::Solution();
    string s = "catsandog";
    vector<string> dict{"cats", "dog", "sand", "and", "cat", "og"};
    auto res = obj->wordBreak(s, dict);
    printf("%d\n", res);
}
