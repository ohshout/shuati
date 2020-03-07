#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        vector<vector<string>> res = dfs(s, 0, words);
        vector<string> ret;
        
        for (auto v : res) {
            string tmp = "";
            for (int i = v.size()-1; i >= 0; i--) {
                tmp = v.at(i) + " ";
            }
            tmp = tmp.substr(0, tmp.size()-1);
            ret.push_back(tmp);
        }
        return ret;
    }
    
    vector<vector<string>> dfs (string s, int idx, unordered_set<string> & words) {
        vector<vector<string>> res;
        
        if (idx == s.size()) {
						res.push_back({""});
            return res;
        }
        
        for (int len = 1; len <= s.size()-1-idx+1; len++) {
            string str = s.substr(idx, len);
            if (words.find(str) != words.end()) {
                cout << str << endl;
                
                vector<vector<string>> ret = dfs(s, idx + len, words);
                
                for (auto v : ret) {
                    v.push_back(str);
                    res.push_back(v);
                }
            }
        }
        
        return res;
    }
};

int main()
{
	Solution sol;
	string s = "catsanddog";
	vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};

	sol.wordBreak(s, wordDict);
}
