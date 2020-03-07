#include <bits/stdc++.h>

using namespace std;

class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) : dp (vector<vector<int>> (matrix.size(), vector<int> (matrix[0].size()))) {
        int sum = 0;
        for (int i = 0; i < dp.size(); i++) {
            sum += matrix[i][0];
            dp[i][0] = sum;
        }
        
        sum = 0;
        for (int i = 0; i < dp[0].size(); i++) {
            sum += matrix[0][i];
            dp[0][i] = sum;
        }
        
        for (int i = 1; i < dp.size(); i++) {
            for (int j = 1; j < dp[0].size(); j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + matrix[i][j];
                cout << dp[i][j] << endl;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int ret = dp[row2][col2];
        if (row1 - 1 >= 0)
            ret -= dp[row1-1][col2];
        if (col1 - 1 >= 0)
            ret -= dp[row2][col1-1];
        if (row1 - 1 >= 0 && col1 - 1 >= 0)
            ret += dp[row1-1][col1-1];
        return ret;
    }
    
private:
    vector<vector<int>> dp;
};

int main()
{
	vector<vector<int>> matrix;
	NumMatrix {matrix};
}


