#include <bits/stdc++.h>

using namespace std;

class NumArray {
public:
    struct node {
        int left; // inclusive
        int right; // inclusive
        int sum;
        
        node(int l, int r, int s) : left(l), right(r), sum(s) {}
    };
    
    vector<node*> segment_tree;
    
    // build the tree and return the sum of the tree
    int build(vector<int>& nums, int idx_in_tree, int left, int right) {
        int val;
        if (left == right) {
            // reach the leaf.
            val = nums.at(left);
        } else {
            // build children first
            int mid = (left + right) / 2;
            val = build(nums, idx_in_tree * 2, left, mid) + 
                build(nums, idx_in_tree * 2 + 1, mid+1, right);
        }
        
        segment_tree[idx_in_tree] = new node(left, right, val);
        
        return val;
    }
    
    
    NumArray(vector<int>& nums) {
        if (nums.size() == 0) 
            return;
        int last_level_node_n = nums.size();
        int h = ceil(log2(last_level_node_n));
        int sz = (int)pow(2, h+1) + 1;

        segment_tree.reserve(sz);
        build(nums, 1, 0, nums.size()-1); // note that idx_in_tree starts with 1!!!
    }
    
    int update_helper(int i, int val, int idx_in_tree) {
        node * n = segment_tree.at(idx_in_tree);
        if (n->left == n->right) {
            int diff = val - n->sum;
            n->sum = val;
            return diff;
        } else {
            // update child first so that we can get the diff to apply
            int mid = (n->left + n->right) / 2;
            if (i > mid) {
                idx_in_tree = idx_in_tree * 2 + 1;
            } else {
                idx_in_tree *= 2;
            }
            int diff = update_helper(i, val, idx_in_tree);
            n->sum += diff;
            return diff;
        }
    }
    
    void update(int i, int val) {
        update_helper(i, val, 1);
    }
    
    int sumRange_helper(int i, int j, int idx_in_tree) {
        node * n = segment_tree.at(idx_in_tree);
        //cout << n->left << " " << n->right << endl;
        if (n->left >= i && n->right <= j) {
            // [n->left, n->right] falls in the query range
            // collect the sum
            return n->sum;
        }

        int mid = (n->left + n->right) / 2;

        if (j <= mid) {
            return sumRange_helper(i, j, idx_in_tree * 2);
        } else if (i > mid) {
            return sumRange_helper(i, j, idx_in_tree * 2 + 1);
        } else {
            return sumRange_helper(i, j, idx_in_tree * 2) +
                sumRange_helper(i, j, idx_in_tree * 2 + 1);
        }
    }
    
    int sumRange(int i, int j) {
        return sumRange_helper(i, j, 1);
    }
};


int main()
{
	vector<int> v {1,3,5};
	NumArray n(v);
	n.sumRange(0,2);
}
