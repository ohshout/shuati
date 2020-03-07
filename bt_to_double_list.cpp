#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode * left; //prev
	TreeNode * right; //next
	TreeNode (int v) : val(v), left(NULL), right(NULL) {}
};


void inorder (TreeNode * node) {
	if (node->left)
		inorder (node->left);
	cout << node->val << " " << endl;
	if (node->right)
		inorder (node->right);
}

//convert binary tree (given root) to a double linked list
//then return the head and tail
pair<TreeNode*, TreeNode*> do_bt2dll (TreeNode * root)
{
	TreeNode* head, *tail;
	pair<TreeNode*, TreeNode*> left, right;
	if (!root->left)
		head = root;
	else {
		left = do_bt2dll (root->left);
		root->left = left.second;
	 	left.second->right = root;
		head = left.first;
	}

	if (!root->right)
		tail = root;
	else {
		right = do_bt2dll (root->right);
		root->right = right.first;
		right.first->left = root;
		tail = right.second;
	}

	return {head, tail};
}

int main()
{
	TreeNode * n25 = new TreeNode (25);
	TreeNode * n30 = new TreeNode (30);
	TreeNode * n11 = new TreeNode (11);
	n30->left = n11;
	TreeNode * n12 = new TreeNode (12);
	n12->left = n25;
	n12->right = n30;
	TreeNode * n15 = new TreeNode (15);
	TreeNode * n36 = new TreeNode (36);
	n15->left = n36;
	TreeNode * n10 = new TreeNode (10);
	n10->left = n12;
	n10->right = n15;
	//inorder(n10);
	auto res = do_bt2dll (n10);
	TreeNode *tmp = res.first;
	while (tmp) {
		cout << tmp->val << endl;
		tmp = tmp->right;
	}
}


