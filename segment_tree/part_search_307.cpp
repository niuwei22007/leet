//
// Created by 鞋底洞 on 2020/10/19.
//
#include "../trust.h"
#include <array>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
namespace partsearch {
    class NumArray {
        vector<int> tree_;
        int size_;
    public:
        NumArray(vector<int> &nums) {
            size_ = nums.size();
            tree_.resize(size_ * 2);
            BuildTree(nums);
        }

        static int LeftChild(int i) {
            return i * 2;
        }

        static int IsLeft(int i) {
            return i % 2 == 0;
        }

        static int RightChild(int i) {
            return i * 2 + 1;
        }

        static int IsRight(int i) {
            return i % 2 == 1;
        }

        static int ParentIndex(int i) {
            return i / 2;
        }


        int TreeIndex(int i) {
            return i + size_;
        }

        void BuildTree(vector<int> &nums) {
            for (int i = nums.size(), j = 0; i < tree_.size(); ++i, ++j) {
                tree_[i] = nums[j];
            }
            for (int i = nums.size() - 1; i > 0; i--) {
                tree_[i] = tree_[LeftChild(i)] + tree_[RightChild(i)];
            }
        }

        void update(int i, int val) {
            i = TreeIndex(i);
            tree_[i] = val;
            while (i > 0) {
                i = ParentIndex(i);
                tree_[i] = tree_[LeftChild(i)] + tree_[RightChild(i)];
            }
        }

        int sumRange(int i, int j) {
            int left = TreeIndex(i);
            int right = TreeIndex(j);
            int sum = 0;
            while (left <= right) {
                if (IsRight(left)) {
                    sum += tree_[left];
                    left++;
                }
                if (IsLeft(right)) {
                    sum += tree_[right];
                    right--;
                }
                left = ParentIndex(left);
                right = ParentIndex(right);
            }
            return sum;
        }
    };
}

void TestForPartSearch() {
    vector<int> list = {1, 2, 3, 4};
    auto *obj = new partsearch::NumArray(list);
    auto result = obj->sumRange(0, 2);
    printf("Result: %d|\n", result);

    obj->update(1, 2);

    result = obj->sumRange(1, 2);
    printf("Result: %d|\n", result);
}
