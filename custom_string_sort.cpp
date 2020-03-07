#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static bool mySort (const char& a, const char& b) {
				//cout << dict[a] << " " << dict[b] << endl;
        return dict[a-'a'] < dict[b-'a'];
    }
    
    string customSortString(string S, string T) {
        
        for (int i = 0; i < S.size(); i++) {
            dict[S[i]-'a'] = i;
        }
        
        sort(T.begin(), T.end(), mySort);
        
        return T;
    }
    
        
private:
     static vector<int> dict;
};

vector<int> Solution::dict (26);

int main()
{
	Solution s;
	cout << s.customSortString ("cba", "abcd") << endl;
}


