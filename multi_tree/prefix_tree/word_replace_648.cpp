//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace replaceword {
    class TrieNode {
    private:
        static const int MAX_LEN = 26;
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
            for (auto c : word) {
                tmp->Add(c);
                tmp = tmp->Get(c);
            }
            tmp->SetEnd(true);
        }

        int startsWith(string prefix) {
            auto tmp = root_;
            int index = 0;
            for (auto c : prefix) {
                if (!(tmp)->Find(c)) {
                    return 0;
                }
                index++;
                tmp = (tmp)->Get(c);
            }
            return prefix.size();
        }

        int Prefix(string &word) {
            auto tmp = root_;
            int index = 0;
            for (auto c : word) {
                if (!tmp->Find(c)) {
                    return 0;
                }
                index++;
                tmp = tmp->Get(c);
                if (tmp->IsEnd()) {
                    return index;
                }
            }
            return index;
        }

        string replaceWords(vector<string> &dictionary, string sentence) {
            if (sentence.empty()) {
                return sentence;
            }
            for (auto word: dictionary) {
                this->Insert(word);
            }
            istringstream split(sentence);
            string word;
            string res;
            while (split >> word) {
                int len = Prefix(word);
                printf("[dbg] len=%d, word=%s\n", len, word.c_str());
                if (len == 0) {
                    res += word + " ";
                } else {
                    res += word.substr(0, len) + " ";
                }
            }
            if (!res.empty()) {
                res.pop_back();
            }
            return res;
        }
    };
}


void TestForWordReplace() {
    auto *solution = new replaceword::Solution();
    vector<string> list = {"cat", "bat", "rat"};
    auto result = solution->replaceWords(list, "the cattle was rattled by the battery bat");
    printf("Result: %s|", result.c_str());
}
