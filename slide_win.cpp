#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int start = -1, end = -1;
        int len = 0;
        char removing = 0;
        map<char, int> v; 
        
        while (end < (int)(s.size()-1)) {
            if (!isalpha(removing)) {
                start++;
								if (start == s.size()) break;
                v[s[start]]++;
                if (v[s[start]] == 2) {
                    removing = s[start];
                } else {
                    len = max(len, start-end);
                }
            } else {
                end++;
                v[s[end]]--;
                if (s[end] == removing) {
                    //removed the one we want to remove
                    removing = 0;
                }
            }
        }
        
        return len;
    }
};

int main()
{
	string s= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	Solution so;
	cout << so.lengthOfLongestSubstring(s) << endl;
}


