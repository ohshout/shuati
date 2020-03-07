#include <bits/stdc++.h>

using namespace std;

int max_size(vector<vector<int>> &dp, int m, int sz) {
	int max_area = -1;

	for (int r = m-1; r < sz; r++) {
		for (int c = m-1; c < sz; c++) {
			int area = dp[r][c];
			if (r-m >=0) {
				area -= dp[r-m][c];
			}
			if (c-m >=0) {
				area -= dp[r][c-m];
			}
			if (r-m >=0 && c-m >=0) {
				area += dp[r-m][c-m];
			}

			max_area = std::max(max_area, area);
		}
	}

	return max_area;
}

int func1(vector<vector<int>> & grid, int maxSum) {
	int sz = grid.size();

	vector<vector<int>> dp(sz, vector<int>(sz));

	// copy the first col
	for (int i = 0; i < sz; i++) {
		dp[0][i] = grid[0][i];
	}

	// compute the rows
	for (int r = 0; r < sz; r++) {
		for (int c = 1; c < sz; c++) {
			dp[r][c] = dp[r][c-1] + grid[r][c];
		}
	}

	// compute the cols
	for (int c = 0; c < sz; c++) {
		for (int r = 1; r < sz; r++) {
			dp[r][c] = dp[r-1][c] + dp[r][c];
		}
	}


	int left = 1, right = sz;

	while (right - left > 1) {
		int m = (left + right)/2;

		int max_area = max_size(dp, m, sz);

		if (max_area == maxSum) {
			return m;
		} else if(max_area > maxSum) {
			// go left
			right = m-1;
		} else {
			left = m;
		}
	}

	if (max_size(dp, right, sz) <= maxSum) {
		return right;
	} else if (max_size(dp, left, sz) <= maxSum) {
		return left;
	} else {
		return 0;
	}
}

int main()
{
	vector<vector<int>> input {{2,2,2},
														 {3,3,3},
														 {4,4,4}};
	cout << func1(input, 300) << endl;
}
