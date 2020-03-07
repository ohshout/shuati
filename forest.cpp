#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_map<int, pair<int,TreeNode*>> m; // id -> <parent_id, node ptr>
        
        queue<TreeNode*> q;
        q.push(root);
        m.insert({root->val, {root->val, root}});
        while(!q.empty()) {
            TreeNode * cur = q.front();
            q.pop();
            if (cur->left != nullptr) {
                q.push(cur->left);
                m.insert({cur->left->val, {cur->val, cur->left}});
            }
            if (cur->right != nullptr) {
                q.push(cur->right);
                m.insert({cur->right->val, {cur->val, cur->right}});
            }
        }
        
        for (int n : to_delete) {
            // two steps:
            // 1. cut off the connection to n's parent
            // 2. cut off the connection to n's children
            // 3. remove myself from the map
            int p_id;
            TreeNode * cur;
            std::tie(p_id, cur) = m[n];
            
            if (p_id == cur->val) {
                // no parent, do nothing
            } else {
                TreeNode * par = m[p_id].second;
                if (par->left == cur) {
                    par->left == nullptr;
                } else {
                    par->right == nullptr;
                }
            }
            
            // children
            if (cur->left != nullptr) {
                int l_id = cur->left->val;
                m[l_id].first = cur->left->val;
            }
            if (cur->right != nullptr) {
                int r_id = cur->right->val;
                m[r_id].first = cur->right->val;
            }
            
            // remove myself
            m[n].second = nullptr;
        }
        
        vector<TreeNode *> res;
        for (auto it = m.begin(); it != m.end(); it++) {
            if (it->second.second != nullptr && it->second.first == it->second.second->val) {
                res.push_back(it->second.second);
            }
        }
        
        return res;
    }
};

int main()
{
	Solution sol;
	TreeNode * one = new TreeNode(1);
	TreeNode * two = new TreeNode(2);
	TreeNode * three = new TreeNode(3);
	TreeNode * four = new TreeNode(4);
	TreeNode * five = new TreeNode(5);
	TreeNode * six = new TreeNode(6);
	TreeNode * seven = new TreeNode(7);
	one->left = two;
	one->right = three;
	two->left = four;
	two->right = five;
	three->left = six;
	three->right = seven;

	vector<int> v{3,5};
	sol.delNodes(one, v);
}




