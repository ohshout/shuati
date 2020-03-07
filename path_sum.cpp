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
    int pathSum(TreeNode* root, int sum) {
			  if (root == nullptr)
					return 0;

        vector<int> path_sums;
        
        return do_path(root, sum, path_sums);
    }
    
    // 1. return number of qualified (path sum == 'sum') paths within subtree of 'root'
    // 2. all the path sums (allow duplicates) starting with root, saved in vector 'p_sums'
    int do_path(TreeNode * root, int sum, vector<int> & p_sums)
    {
        int cnt = 0;
        vector<int> l_sums, r_sums;
        
        if (root->left) {
            cnt += do_path(root->left, sum, l_sums);
        }
        
        if (root->right) {
            cnt += do_path(root->right, sum, r_sums);
        }
        
        // merge l_sums and r_sums
        l_sums.insert(l_sums.end(), r_sums.begin(), r_sums.end());
        
        // now connect those paths with current node
				std::transform(l_sums.begin(), l_sums.end(), l_sums.begin(), [root](int x){return x+root->val;});
        
        // add current node
        l_sums.push_back(root->val);
        
        // check if there is sum
        cnt += count(l_sums.begin(), l_sums.end(), sum);
        
        // return
        p_sums.insert(p_sums.end(), l_sums.begin(), l_sums.end());
        return cnt;
    }
};

int main()
{
	TreeNode * parent = new TreeNode{1};
	//TreeNode * left = new TreeNode{1};
	//TreeNode * right = new TreeNode{1};
	//parent->left = left;
	//parent->right = right;
	Solution sol;
	cout << sol.pathSum(parent, 1) << endl;

}
