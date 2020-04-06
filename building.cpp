#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct trip {
        int loc;
        int num;
        bool isoff;
    };
    
    struct cmpTrips {
        bool operator()(trip const & t1, const trip & t2) const {
            if (t1.loc == t2.loc) {
                return t1.isoff;
            } else {
                return t1.loc < t2.loc;
            }
        }
    };
    
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<trip> ts;
        
        for (auto & t : trips) {
            ts.push_back({t[1], t[0], false});
            ts.push_back({t[2], t[0], true});
        }
        
        sort(ts.begin(), ts.end(), cmpTrips());
        
        int count = 0;
        for (auto & t : ts) {
            if (!t.isoff) {
                count += t.num;
                if (count > capacity) return false;
            } else {
                count -= t.num;
            }
        }
        
        return true;
    }
};

int main()
{
	Solution sol;
	vector<vector<int>> v{{7,2,5},{10,1,3},{4,2,8},{2,3,6},{3,1,8},{7,1,7},{3,3,6},{1,2,8},{8,2,8}};
	sol.carPooling(v, 41);
}

