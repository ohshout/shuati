#include <bits/stdc++.h>

using namespace std;

void calc_prob_tab (vector<vector<double>>& tab)
{
	tab[0][1] = tab[1][0] = 0.5;
	int m = tab.size(), n = tab[0].size();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i > 0) {
				if (j == n-1)
					tab[i][j] += tab[i-1][j];
				else
					tab[i][j] += tab[i-1][j] * 0.5;
			}
			if (j > 0) {
				if (i == m-1)
					tab[i][j] += tab[i][j-1];
				else
					tab[i][j] += tab[i][j-1] * 0.5;
			}
		}
	}
}

double calc_mean (vector<vector<double>>& tab)
{
	double mean = 0.0;
	double m = tab.size(), n = tab[0].size();
	for (double x = 0; x < m; x++) {
		for (double y = 0; y < n; y++) {
			double D = max ((x/m)-(y/n), (y/n)-(x/m));
			cout << D * tab[x][y] << endl;
			mean += D * tab[x][y];
		}
	}
	return mean;
}

int main ()
{
	int m = 2, n = 2;
	vector<vector<double>> tab (m+1, vector<double> (n+1, 0));
	calc_prob_tab (tab);
	/*
	for (int i = 0; i < tab.size(); i++) {
		for (int j = 0; j < tab[0].size(); j++) {
			cout << "(" << i << "," << j << "): " << tab[i][j] << endl;
		}
	}
	*/
	cout << calc_mean(tab) << endl;
}


