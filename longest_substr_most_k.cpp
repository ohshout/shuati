#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
      int start = -1, end = -1, len = 0;
      unordered_map<char, int> M; //<letter, freq>
      while (end < (int)(s.size()-1)) {
        if (M.size() <= k) {
          //enlarge window by moving end
          ++end;
          ++M[s[end]];
        } else {
          //shrink window by moving start
          ++start;
          --M[s[start]];
          if (M[s[start]] == 0)
            M.erase(s[start]);
        }
        if (M.size() <= k) {
          len = max(len, end-start);
					cout << len << " " << end << " " << start << endl;
				}
      }
      return len;
    }
};

int main()
{
	Solution s;
	cout << s.lengthOfLongestSubstringKDistinct ("eceba", 2) << endl;
}


