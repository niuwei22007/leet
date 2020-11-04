//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

using namespace std;
namespace search_word2 {
class Solution {
    struct TrieNode {
        string word;
        vector<TrieNode *> child;

        TrieNode() {
            child = vector<TrieNode *>(26);
        }
    };

    vector<string> ans_;
public:
    void DFS(vector<vector<char>> &board, vector<vector<bool>> &used, int row, int col, TrieNode *node) {
        if (used[row][col]) {
            return;
        }
        int index = board[row][col] - 'a';
        TrieNode *child = node->child[index];
        if (child == nullptr) {
            return;
        }
        if (!child->word.empty()) {
            ans_.push_back(child->word);
            child->word.clear();
        }
        used[row][col] = true;
        // up
        if (row > 0) DFS(board, used, row - 1, col, child);
        // down
        if ((row + 1) < board.size()) DFS(board, used, row + 1, col, child);
        // left
        if (col > 0) DFS(board, used, row, col - 1, child);
        // right
        if ((col + 1) < board[0].size()) DFS(board, used, row, col + 1, child);

        used[row][col] = false;
    }

    vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
        if (board.empty() || board[0].empty() || words.empty()) {
            return vector<string>();
        }
        auto *root = new TrieNode();

        for (auto &w:words) {
            TrieNode *tmp = root;
            for (auto c : w) {
                if (tmp->child[c - 'a'] == nullptr) {
                    tmp->child[c - 'a'] = new TrieNode();
                }
                tmp = tmp->child[c - 'a'];
            }
            tmp->word = w;
        }
        vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                DFS(board, used, i, j, root);
            }
        }
        return ans_;
    }
};
}

void TestForSearchWord2() {
    auto *obj = new search_word2::Solution();
    vector<vector<char>> board{
            {'o', 'a', 'a', 'n'},
            {'e', 't', 'a', 'e'},
            {'i', 'h', 'k', 'r'},
            {'i', 'f', 'l', 'v'}
    };
    vector<string> words{"oath", "ea", "eat", "rain", "kl"};
    auto result = obj->findWords(board, words);
    for (auto &w:result) {
        printf("---- %s\n", w.c_str());
    }
}
