#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> adjList (numCourses);
        
        for (pair<int, int> & p : prerequisites) {
            adjList[p.second].push_back(p.first);
        }
        
        vector<bool> visited (numCourses, false);
        vector<bool> g_visited(numCourses, false);
        
        for (int i = 0; i < numCourses; i++) {
            if (g_visited[i] == true) 
                continue;
            else {
                bool ret = dfs(numCourses, adjList, i, visited, g_visited);
                if (ret == false)
                    return false;
            }
        }
        
        return true;
    }
    
    bool dfs(int numCourses, vector<vector<int>> & adjList, int node, 
             vector<bool> & visited, vector<bool> & g_visited) {
        return true;
        g_visited[node] = true;
        
        vector<int> nei = adjList[node];
        for (int n : nei) {
            if (visited[n] == true) {
                return false;
            }
            visited[n] = true;
            bool ret = dfs(numCourses, adjList, n, visited, g_visited);
            if (ret == false)
                return false;
            visited[n] = false;
        }
        
        return true;
    }
};

int main()
{
	Solution sol;
  vector<pair<int, int>> prerequisites {std::make_pair(1, 0)};
	cout << sol.canFinish(2, prerequisites) << endl;
}
