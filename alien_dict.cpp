#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        array<vector<char>, 26> adjList;
        array<int, 26> visited; // -1 nonexist, 0 unvisited, 1 local, 2 global
				std::fill(visited.begin(), visited.end(), -1);
				
        
        string prev = "";
        
        for (string & str : words) {
						for (char c : str) {
							visited[c-'a'] = 0;
						}

            if (prev != "") {
                for (int i = 0; i < prev.size(); i++) {
                    if (prev[i] != str[i]) {
                        adjList[prev[i]-'a'].push_back(str[i]);
                    }
                }
            }
            prev = str;
        }
        
        
        // topological sort
        string res = "";
        
        for (int i = 0; i < 26; i++) {
            if (visited[i] == 0) {
                if (dfs('a'+i, adjList, visited, res)) {
                    return "";
                }
            }   
        }
        
        std::reverse(res.begin(), res.end());
        return res;
    }
    
    bool dfs(char cur, array<vector<char>, 26> & adjList, array<int, 26> & visited, string & res) {
        for (auto & neighbor : adjList[cur-'a']) {
            if (visited[neighbor-'a'] == 1) {
                // loop detected
                res = "";
                return true;
            } else if (visited[neighbor-'a'] == 0) {
                // visit neighbor first
                visited[neighbor-'a'] = 1;
                bool isloop = dfs(neighbor, adjList, visited, res);
                if (isloop) {
                    return true;
                }
                // when we get back, neighbor should have been marked as globally visited, so no need to backtrack
            }
        }
        
        // have visited all of its neighbors
        visited[cur-'a'] = 2;
        res += cur;
        return false;
    }
};

int main()
{
	Solution sol;
	vector<string> v {"wrt", "wrf", "er", "ett", "rftt"};
  string res = sol.alienOrder(v);
	cout << res << endl;
}
