//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
namespace longest {
    class TrieNode {
    private:
        static const int MAX_LEN = 26;
        array<TrieNode *, MAX_LEN> next_{nullptr};
        bool isEnd_ = false;
        string word_ = "";
    public:
        explicit TrieNode(bool isEnd = false, string word = "") : isEnd_(isEnd), word_(word) {

        }

        bool Find(char c) {
            return (next_[c - 'a'] != nullptr);
        }

        TrieNode *Get(char c) {
            return next_[c - 'a'];
        }

        void Add(char c) {
            if (!Find(c)) {
                next_[c - 'a'] = new TrieNode();
            }
        }

        void SetEnd(bool end) {
            this->isEnd_ = end;
        }

        bool IsEnd() {
            return this->isEnd_;
        }

        void SetWord(string& word) {
            this->word_ = word;
        }

        string GetWord() {
            return this->word_;
        }

        array<TrieNode*, MAX_LEN> GetNodeList() const {
            return this->next_;
        }
    };

    class Solution {
    private:
        TrieNode *root_;
    public:
        Solution() {
            root_ = new TrieNode();
        }

        void Insert(string &word) {
            auto tmp = root_;
            int level = 0;
            for (auto c : word) {
                tmp->Add(c);
                level++;
                tmp = tmp->Get(c);
            }
            tmp->SetEnd(true);
            tmp->SetWord(word);
        }

        void DFS(TrieNode* node, string& longest) {
            if (node->GetWord().size() > longest.size()) {
                longest = node->GetWord();
            }
            for (auto n : node->GetNodeList()) {
                if (n != nullptr && n->IsEnd()) {
                    DFS(n, longest);
                }
            }
        }

        string longestWord(vector<string> &words) {
            for (auto w : words) {
                this->Insert(w);
            }
            string res;
            DFS(this->root_, res);
            return res;
        }

    };
}

void TestForLongestWord() {
    auto *solution = new longest::Solution();
    vector<string> list = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
    auto result = solution->longestWord(list);
    printf("Result: %s|", result.c_str());
}
