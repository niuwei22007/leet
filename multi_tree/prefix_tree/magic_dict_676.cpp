//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
namespace magicdict {
    static const int MAX_LEN = 26;

    class TrieNode {
    private:
        array<TrieNode *, MAX_LEN> next_{nullptr};
        bool isEnd_ = false;
    public:
        explicit TrieNode(bool isEnd = false) : isEnd_(isEnd) {

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

        array<TrieNode *, MAX_LEN> GetNodeList() const {
            return this->next_;
        }
    };

    class MagicDictionary {
    private:
        TrieNode *root_;
    public:
        MagicDictionary() {
            root_ = new TrieNode();
        }

        void Insert(string &word) {
            auto tmp = root_;
            for (auto c : word) {
                tmp->Add(c);
                tmp = tmp->Get(c);
            }
            tmp->SetEnd(true);
        }

        void buildDict(vector<string> dictionary) {
            for (auto word : dictionary) {
                this->Insert(word);
            }
        }

        bool DFS(string &searchWord, int index, int diffCount, TrieNode *node) {
            if (index == searchWord.size()) {
                return diffCount == 0 && node->IsEnd();
            }
            for (int i = 0; i < MAX_LEN; i++) {
                if (node->GetNodeList()[i] == nullptr) {
                    continue;
                }
                if (i == (searchWord[index] - 'a')) {
                    if (DFS(searchWord, index + 1, diffCount, node->GetNodeList()[i])) {
                        return true;
                    }
                } else {
                    if ((diffCount - 1) >= 0 && DFS(searchWord, index + 1, diffCount - 1, node->GetNodeList()[i])) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool search(string searchWord) {
            if (searchWord.empty()) {
                return false;
            }
            return DFS(searchWord, 0, 1, this->root_);
        }
    };
}


void TestForMagicDict() {
    auto *magicDictionary = new magicdict::MagicDictionary();
    vector<string> dict{"hello", "hallo", "leetcode", "judge", "judgg"};
    magicDictionary->buildDict(dict);

    vector<string> searchs{"hello", "hallo", "hell", "leetcodd", "judge", "juggg"};
    for (auto s : searchs) {
        bool res = magicDictionary->search(s);
        printf("Search:%s, Res: %s\n", s.c_str(), res ? "true" : "false");
    }
}