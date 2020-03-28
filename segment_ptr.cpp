#include <bits/stdc++.h>

using namespace std;

class NumArray {
public:
    struct STNode {
        int left; // inclusive
        int right; // inclusive
        int sum;
        STNode * leftTree;
        STNode * rightTree;
        
        STNode(int l, int r, int s) : left(l), right(r), sum(s), leftTree(nullptr), rightTree(nullptr) {}
    };
    
    STNode * root_;
    
    STNode * insert(vector<int>& nums, STNode * root, int left, int right) {
        if (left == right) {
            root = new STNode(left, right, nums.at(left));
        } else {
            int mid = (left + right) / 2;
            root = new STNode(left, right, 0);

            STNode * leftT = insert(nums, root->leftTree, left, mid);
            STNode * rightT = insert(nums, root->rightTree, mid+1, right);
            
						root->leftTree = leftT;
						root->rightTree = rightT;
						root->sum = leftT->sum + rightT->sum;
        }
        
        return root;
    }
    
    NumArray(vector<int>& nums) {
        if (nums.size() == 0) 
            return;
        
        root_ = insert(nums, root_, 0, nums.size()-1);
    }
    
    int update_helper(STNode * n, int i, int val) {
        if (n == nullptr) {
            return 0;
        }
        
        if (n->left == n->right) {
            int diff = val - n->sum;
            n->sum = val;
            return diff;
        } else {
            // update child first so that we can get the diff to apply
            int mid = (n->left + n->right) / 2;
            int diff;
            if (i > mid) {
                diff = update_helper(n->rightTree, i, val);
            } else {
                diff = update_helper(n->leftTree, i, val);
            }
            
            n->sum += diff;
            return diff;
        }
    }
    
    void update(int i, int val) {
        update_helper(root_, i, val);
    }
    
    int sumRange_helper(STNode * root, int i, int j) {
        if (root == nullptr) {
            return 0;
        }
        
        if (root->left >= i && root->right <= j) {
            // [root->left, root->right] falls in the query range
            // collect the sum
            return root->sum;
        }

        int mid = (root->left + root->right) / 2;

        if (j <= mid) {
            return sumRange_helper(root->leftTree, i, j);
        } else if (i > mid) {
            return sumRange_helper(root->rightTree, i, j);
        } else {
            return sumRange_helper(root->leftTree, i, j) +
                    sumRange_helper(root->rightTree, i, j);
        }
    }
    
    int sumRange(int i, int j) {
        return sumRange_helper(root_, i, j);
    }
};

int main()
{
	vector<int> v {1,3,5};
	NumArray n(v);
	cout << "build okay" << endl;
	cout << n.sumRange(0,2) << endl;
	n.update(1,2);
	cout << n.sumRange(0,2) << endl;
}
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */


