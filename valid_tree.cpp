#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if (n == 1)
            return true;
        vector<int> parent(edges.size());
        for (int i = 0; i < n; i++)
            parent[i] = i;
        
        for (auto p: edges) {
            int par1 = find(parent, p.first);
            int par2 = find(parent, p.second);
            if (par1 == par2)
                return false;
            else
                Union(parent, par1, par2);
        }
        
        int group = find(parent, 0);
        for (int i = 1; i < n; i++) {
            if (group != find(parent, i))
                return false;
        }
        return true;
    }
    
    int find(vector<int>& parent, int node) {
        while (parent[node] != node) {
            node = parent[node];
        }
        return node;
    }
    
    void Union (vector<int>& parent, int n1, int n2) {
        parent[n1] = n2;
    }
};

int main()
{
	Solution s;
	vector<pair<int,int>> v;
	cout << s.validTree (2, v) << endl;
}
