#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct Node {
        int start;
        int end;
        int index;
        Node * left;
        Node * right;
        
        Node (int s, int e, int i) : start(s), end(e), index(i), left(nullptr), right(nullptr) {}
    };
    
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
				int sz = intervals.size();
        vector<int> res (sz);
        
        Node * root = nullptr;
        for (int i = 0; i < sz; i++) {
            Node * tmp = new Node(intervals[i][0], intervals[i][1], i);
            root = insert(root, tmp);
        }
        
        for (int i = 0 ; i < sz; i++) {
            Node * tmp = new Node(intervals[i][0], intervals[i][1], i);
            res[i] = search(root, tmp);
						delete tmp;
        }
        
        return res;
    }
    
    Node * insert(Node * root, Node * n) {
        if (root == nullptr) 
            return n;
        
        if (root->start > n->start) {
            // go left
            root->left = insert(root->left, n);
        } else {
            // go right
            root->right = insert(root->right, n);
        }
        
        return root;
    }
    
    int search(Node * root, Node * n) {
        int idx = -1;
        
        while(root != nullptr) {
            if (root->start >= n->end) {
                // root on the right
								idx = root->index;
								
                // but root might not be the leftmost one that is on the right of n
                // so go left
                root = root->left;
            } else {
                // have to go right to find a larger start
                root = root->right;
            }
        }
        
        return idx;
    }
};

int main()
{
	Solution sol;
	vector<vector<int>> v {{3,4},{2,3},{1,2}};
	vector<int> res = sol.findRightInterval(v);
	for (int n: res) {
		cout << n << endl;
	}
	return 0;
}
