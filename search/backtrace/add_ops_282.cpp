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
#include <queue>

using namespace std;
namespace add_operators {
class Solution {
public:
    void Backtrack(const string& num, int target,
                   int currentIdx, long currentVal, string& currentForm,
                   long prevVal, vector<string>& ans) {
        if (currentIdx == num.length()) {
            if (currentVal == target) {
                ans.push_back(currentForm);
            }
            return;
        }

        size_t formLen = currentForm.length();
        for (int i = currentIdx; i < num.length(); i++) {
            string element = num.substr(currentIdx, i - currentIdx + 1);
            long eleVal = stol(element);
            if (currentForm.empty()) {
                currentForm += element;
                Backtrack(num, target, i + 1, eleVal, currentForm, eleVal, ans);
                currentForm.resize(formLen);
            } else {
                if (currentVal < target) {
                    currentForm += "+" + element;
                    Backtrack(num, target, i + 1, currentVal + eleVal, currentForm, eleVal, ans);
                    currentForm.resize(formLen);
                }

                currentForm += "-" + element;
                Backtrack(num, target, i + 1, currentVal - eleVal, currentForm, -eleVal, ans);
                currentForm.resize(formLen);

                currentForm += "*" + element;
                Backtrack(num, target, i + 1, currentVal - prevVal + prevVal * eleVal, currentForm, prevVal * eleVal,
                          ans);
                currentForm.resize(formLen);
            }
            if (eleVal == 0) {
                return;
            }
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        if (num.empty()) {
            return ans;
        }
        if (to_string(target) == num) {
            ans.push_back(num);
            return ans;
        }
        string form;
        Backtrack(num, target, 0, 0, form, 0, ans);
        return ans;
    }
};
}

void TestForAddOperators() {
    auto* obj = new add_operators::Solution();
    auto res = obj->addOperators("123", 6);
    for (const auto& r : res) {
        printf("%s\n", r.c_str());
    }
}
