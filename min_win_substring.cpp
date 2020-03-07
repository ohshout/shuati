#include <bits/stdc++.h>

using namespace std;

/*
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size())
            return "";
        map<char,int> M; //<letter, freq>
        int to_be_matched = 0;
        for (char c: t) {
            M[c]++;
            to_be_matched++;
        }
        int next2add = 0, next2remove = 0;
        string res = "";
        int minL = INT_MAX;
        
        while (1) {
            if (to_be_matched > 0) {
                //expand to match
                if (next2add == s.size())
                    break;
                char c = s[next2add];
                next2add++;
                if (M.find(c) != M.end()) {
                    if (M[c] > 0)
                        to_be_matched--;
                    M[c]--;
                }
            } else {
                int len = next2add-next2remove;
                if (len < minL) {
                    res = s.substr(next2remove, len);
                    minL = len;
                }
                
                //shrink to find min len
                if (next2remove == s.size())
                    break;
                char c = s[next2remove];
                next2remove++;
                if (M.find(c) != M.end()) {
                    if (M[c] >= 0)
                        to_be_matched++;
									  M[c]++;
                }
            }
        }
        
        return res;
    }
};
*/

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size())
            return "";
        map<char,int> to_be_matched; //<letter, freq>
        int n2match = 0;
        for (char c: t) {
            to_be_matched[c]++;
            n2match++;
        }
        int l = 0;
        string res = "";
        int minL = INT_MAX;
        
        for (int r = 0; r < s.size(); r++) {
            char c = s[r];
            if (to_be_matched.find(c) != to_be_matched.end()) {
                to_be_matched[c]--;
                if (to_be_matched[c] >= 0) n2match--;
            }
            while (n2match == 0) {
                int len = r-l+1;
                if (len < minL) {
                    res = s.substr(l, len);
                    len = minL;
                }
                char c = s[l];
                if (to_be_matched.find(c) != to_be_matched.end()) {
                    to_be_matched[c]++;
                    if (to_be_matched[c] > 0) n2match++;
                }
                l++;
            }
        }
        
        return res;
    }
};

int main()
{
	Solution sol;
	cout << sol.minWindow ("cabwefgewcwaefgcf", "cae") << endl;
}


