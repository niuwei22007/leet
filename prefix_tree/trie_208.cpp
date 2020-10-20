//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../trust.h"
#include <string>
#include <array>

using namespace std;
namespace trie {
    static const int MAX_LEN = 26;

    class TrieNode {
    public:
        TrieNode(bool end = false) : isEnd_(end) {
            nextNode_.fill(nullptr);
        }

        bool Find(char c) {
            return (nextNode_[c - 'a'] != nullptr);
        }

        bool Add(char c) {
            if (nextNode_[c - 'a'] != nullptr) {
                return false;
            }
            nextNode_[c - 'a'] = make_shared<TrieNode>();
            return true;
        }

        shared_ptr<TrieNode> Get(char c) {
            return nextNode_[c - 'a'];
        }

        void SetEnd(bool end) {
            this->isEnd_ = end;
        }

        bool IsEnd() {
            return this->isEnd_;
        }

    private:
        array<shared_ptr<TrieNode>, MAX_LEN> nextNode_{};
        bool isEnd_;
    };

    class Trie {
    public:
        /** Initialize your data structure here. */
        Trie() {
            root_ = make_shared<TrieNode>();
        }

        /** Inserts a word into the trie. */
        void insert(string word) {
            auto tmp = root_;
            for (auto c : word) {
                if (!(tmp)->Find(c)) {
                    (tmp)->Add(c);
                }
                tmp = (tmp)->Get(c);
            }
            (tmp)->SetEnd(true);
        }

        /** Returns if the word is in the trie. */
        bool search(string word) {
            auto tmp = root_;
            for (auto c : word) {
                if (!(tmp)->Find(c)) {
                    return false;
                }
                tmp = (tmp)->Get(c);
            }
            return (tmp)->IsEnd();
        }

        /** Returns if there is any word in the trie that starts with the given prefix. */
        bool startsWith(string prefix) {
            auto tmp = root_;
            for (auto c : prefix) {
                if (!(tmp)->Find(c)) {
                    return false;
                }
                tmp = (tmp)->Get(c);
            }
            return true;
        }

    private:
        shared_ptr<TrieNode> root_;
    };
}


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

void TestForTrie() {
    auto *trie = new trie::Trie();
    trie->insert("apple");
    bool res = trie->search("app");
    printf("search app: %d\n", res);
    res = trie->startsWith("app");
    printf("startsWith app: %d", res);
}