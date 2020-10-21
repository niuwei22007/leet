//
// Created by 鞋底洞 on 2020/10/20.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <queue>

using namespace std;
namespace mapsum {
    static const int MAX_LEN = 26;

    class TrieNode {
    private:
        array<TrieNode *, MAX_LEN> next_{nullptr};
        int val_ = 0;
        bool isEnd_ = false;
    public:
        explicit TrieNode(int val = 0) : val_(val) {

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

        void SetValue(int val) {
            this->val_ = val;
        }

        int GetValue() {
            return this->val_;
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

    class MapSum {
    private:
        TrieNode *root_{nullptr};
//    map<string, int> dict_;
    public:
        /** Initialize your data structure here. */
        MapSum() {
            root_ = new TrieNode();
        }

        void Put(string &word, int val) {
            auto tmp = root_;
            for (auto c : word) {
                tmp->Add(c);
                tmp = tmp->Get(c);
            }
            tmp->SetValue(val);
            tmp->SetEnd(true);
        }

        void DFS(TrieNode *node, int &sum) {
            if (node->IsEnd()) {
                sum += node->GetValue();
            }
            for (auto n : node->GetNodeList()) {
                if (n != nullptr) {
                    DFS(n, sum);
                }
            }
        }

        int PrefixSum(string &word) {
            auto tmp = root_;
            for (auto c:word) {
                if (!tmp->Get(c)) {
                    return 0;
                }
                tmp = tmp->Get(c);
            }
            int sum = 0;
            DFS(tmp, sum);
            return sum;
        }

        bool StartWith(string &context, string &prefix) {
            return context.compare(0, prefix.size(), prefix) == 0;
        }

        bool EndWith(string &context, string &suffix) {
            return context.size() >= suffix.size() &&
                   context.compare(context.size() - suffix.size(), suffix.size(), suffix) == 0;
        }

        void insert(string key, int val) {
//        dict_[key] = val;
            this->Put(key, val);
        }

        int sum(string prefix) {
//        int numSum = 0;
//        for (auto kv : dict_) {
//            if (StartWith(kv.first, prefix)) {
//                numSum += kv.second;
//            }
//        }
//
//        return numSum;
            return PrefixSum(prefix);
        }
    };
}


/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
