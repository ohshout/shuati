#include <bits/stdc++.h>

using namespace std;

class Solution {
	public:
		int longestPalindromeSubseq(string s) {
			int len = 1;
			vector<vector<int>> dp (s.size(), vector<int> (s.size()));
			while (len <= s.size()) {
				for (int sIdx = 0; sIdx + len - 1 <= s.size()-1; sIdx++) {
					if (len == 1) {
						dp[sIdx][sIdx] = 1; //single char is palindrome
					} else if (len == 2) {
						int eIdx = sIdx + len - 1;
						if (s[sIdx] == s[eIdx]) dp[sIdx][eIdx] = 2;
						else dp[sIdx][eIdx] = 1;
					} else {
						int eIdx = sIdx + len - 1;
						if (s[sIdx] == s[eIdx]) dp[sIdx][eIdx] = dp[sIdx+1][eIdx-1] + 2;
						else dp[sIdx][eIdx] = max(dp[sIdx+1][eIdx], dp[sIdx][eIdx-1]);
					}
				}
				len++;
			}

			return dp[0][s.size()-1];
		}
};

int main()
{
	Solution s;
	cout << s.longestPalindromeSubseq ("bbbab") << endl;
}


