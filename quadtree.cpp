#include <bits/stdc++.h>

using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        return do_construct(grid, 0, 0, grid.size());
    }
    
    Node * do_construct(vector<vector<int>>& grid, int row, int col, int len) {
        if (len == 1) {
           return new Node(!!grid[row][col], true, nullptr, nullptr, nullptr, nullptr); 
        } else {
            Node *root = new Node();
            vector<Node*> children (4, nullptr);
            int dir[] = {0, 0, 1, 1, 0}; //tl, tr, br, bl 
            for (int i = 0; i < 4; i++) {          
                Node * child = do_construct(grid, row + len/2*dir[i], col + len/2*dir[i+1], len/2);
                children[i] = child;
            }
            
            int i;
            bool val;
            for (i = 0; i < 4; i++) {
                Node *child = children[i];
                if (child->isLeaf == false) {
                    break;
                }
                if (i == 0) {
                    val = child->val;
                } else if (val != child->val) {
                    break;
                }
            }
            
            if (i == 4) {
                // all children are leaves and have the same val
                // unify them
                root->isLeaf = true;
                root->val = val;
                for (Node * n : children) {
                    delete n;
                }
            } else {
                root->isLeaf = false;
                root->val = false;
                root->topLeft = children[0];
                root->topRight = children[1];
                root->bottomRight = children[2];
                root->bottomLeft = children[3];
            }
            
            return root;
        }
    }
};

void printQuadTree(Node *n, string s) {
	cout << s;
	if (s != "") {
		cout << "|__";
	}
	cout << n->isLeaf << " " << n->val << endl;
	if (n->isLeaf == false) {
		printQuadTree(n->topLeft, s + "   ");
		printQuadTree(n->topRight, s + "   ");
		printQuadTree(n->bottomLeft, s + "   ");
		printQuadTree(n->bottomRight, s + "   ");
	}
}

int main()
{
	vector<vector<int>> v = {{{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}}};
	Solution s;
	Node * res = s.construct(v);
	printQuadTree(res, "");
	return 0;
}
