#include <bits/stdc++.h>


using namespace std;

class MyCalendarThree {
public:
    struct TreeNode {
        int start;
        int end;
        int max_end;
        TreeNode * right;
        TreeNode * left;
        
        TreeNode (int s, int e) : start(s), end(e), max_end(end), right(nullptr), left(nullptr) {}
    };
    
    TreeNode * root_ = nullptr;
    int max_booking = -1;
    
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        //cout << "-------------------" << endl;
        //cout << start << " " << end << endl;
        
        int res = 1;
        TreeNode * tmp = new TreeNode (start, end);
        if (root_ != nullptr) {
            res += search(root_, tmp);
        }
        
        root_ = insert(root_, tmp);
        max_booking = std::max(max_booking, res);
        
        return max_booking;
    }
    
    TreeNode * insert(TreeNode * root, TreeNode * n) {
        if (root == nullptr) {
            return n;
        }
        
        if (root->start > n->start) {
            root->left = insert(root->left, n);
        } else {
            root->right = insert(root->right, n);
        }
        root->max_end = std::max(root->max_end, n->end);
        
        return root;
    }
    
    int search(TreeNode * root, TreeNode * n) {
        if (n->end <= root->start) {
            // -----      n
            //      ****  root
            // might overlap in the left subtree
            if (root->left != nullptr && root->left->max_end > n->start) {
                return search(root->left, n);
            }
            return 0;
        } else {
            //       ----- n
            // *****       root
            // might overlap both subtree
            int res;
            if (n->start >= root->end) {
                res = 0;
            } else {
                res = 1;
            }
            
            if (root->left != nullptr && root->left->max_end > n->start)  {
                res += search(root->left, n);
            }
            if (root->right != nullptr && root->right->max_end > n->start) {
                res += search(root->right, n);
            }
            return res;
        }
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */

int main()
{
	MyCalendarThree* obj = new MyCalendarThree();
	vector<vector<int>> v {{24,40},{43,50},{27,43},{5,21},{30,40},{14,29},{3,19},{3,14},{25,39},{6,19}};

	for (vector<int> & interval : v) {
		int k = obj->book(interval[0],interval[1]);
		cout << k << endl;
	}

	return 0;
}
