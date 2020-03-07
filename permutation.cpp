#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        
        stack<pair<vector<int>, vector<int>>> S;
        S.push({{}, nums});
        
        while (!S.empty()) {
            auto p = S.top();
            S.pop();
            
            vector<int> cur = p.first;
            vector<int> rem = p.second;
            
            if (rem.size() == 0) {
                res.push_back(cur);
                continue;
            }
            
            for (int i = 0; i < rem.size(); i++) {
                vector<int> new_cur = cur;
                new_cur.push_back(rem[i]);
                vector<int> new_rem = rem;
                new_rem.erase(new_rem.begin() + i);
                S.push({new_cur, new_rem});
            }
        }
        
        return res;
    }
};

int main()
{
	Solution s;
	vector<int> v {1,2,3};
	auto res = s.permute (v);
}

