#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<vector<double>>> M (N, vector<vector<double>> (N, vector<double> (K+1,-1)));
        return do_kp (N, K, r, c, M);
    }
    
    double do_kp (int N, int K, int r, int c, vector<vector<vector<double>>>& M) {
        //guaranteed within board
        double ret;
        if (K == 0) // end position and we are within the board, so probability == 1
            ret = 1;
        else {
            // K > 0
            double prob = 0.0;
            for (int i = 0; i < dir.size(); i++) {
                int new_r = r+dir[i].first;
                int new_c = c+dir[i].second;
                if (new_r < 0 || new_r >= N) //out of board
                    continue;
                if (new_c < 0 || new_c >= N) //out of board
                    continue;
                if (M[new_r][new_c][K-1] == -1)
                    prob += do_kp (N, K-1, new_r, new_c, M);
                else
                    prob += M[new_r][new_c][K-1];
            }
            ret = prob / 8;
        }
				
        M[r][c][K] = ret;
				cout << r << " " << c << " " << K << " " << M[r][c][K] << endl;
        return ret;
    }
    
private:
    vector<pair<int, int>> dir {{-2,1}, {-1,2}, {1,2}, {2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}};
};

int main()
{
	Solution s;
	cout << s.knightProbability (8, 30, 6, 4) << endl;
}
