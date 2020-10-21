//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
namespace triesearch {
    class TrieNode {
    private:
        static const int MAX_LEN = 26;
        array<TrieNode *, MAX_LEN> next_{nullptr};
        int weight_ = -1;
//        char c_;
    public:
        explicit TrieNode(int weight = -1) : weight_(weight) {

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
//                this->c_ = c;
            }
        }

        void SetWeight(int weight) {
            this->weight_ = weight;
        }

        int GetWeight() {
            return this->weight_;
        }

        bool IsEnd() {
            return this->weight_ > -1;
        }

        array<TrieNode *, MAX_LEN> GetNodeList() const {
            return this->next_;
        }
    };

    class WordFilter {
    private:
        TrieNode *root_;
        vector<string> words_;
    public:
        WordFilter(vector<string> &words) {
            this->root_ = new TrieNode();
            this->words_ = words;
            for (int i = 0; i < words.size(); i++) {
                this->Insert(words[i], i);
            }
        }

        int f(string prefix, string suffix) {
            auto tmp = this->root_;
            for (auto c : prefix) {
                if (!tmp->Find(c)) {
                    return -1;
                }
                tmp = tmp->Get(c);
            }
            int max = -1;
            DFS(tmp, suffix, max);
            return max;
        }

        bool EndWith(string &context, string &suffix) {
            return context.size() >= suffix.size() &&
                   context.compare(context.size() - suffix.size(), suffix.size(), suffix) == 0;
        }

        void Insert(string &word, int weight) {
            auto tmp = root_;
            int level = 0;
            for (auto c : word) {
                tmp->Add(c);
                level++;
                tmp = tmp->Get(c);
            }
            tmp->SetWeight(weight);
        }

        void DFS(TrieNode *node, string &suffix, int &max) {
            if (node->GetWeight() > max && this->EndWith(words_[node->GetWeight()], suffix)) {
                max = node->GetWeight();
            }
            for (auto n : node->GetNodeList()) {
                if (n != nullptr) {
                    DFS(n, suffix, max);
                }
            }
        }

    };
}

void TestForTrieSearch() {
    vector<string> list = {"apple", "hello", "abcde"};
    auto *obj = new triesearch::WordFilter(list);
    int result = obj->f("a", "d");
    printf("Result: %d|", result);
}
