#include <bits/stdc++.h>

using namespace std;

void do_cc (int amount, vector<int>& coins, int idx, int& count) {
	if (amount == 0)
		count++;
	else {
		for (int i = idx; i < coins.size(); i++) {
			if (coins[i] <= amount)
				do_cc (amount-coins[i], coins, i, count);
		}
	}
}

int coinChange (int amount, vector<int>& coins) {
	int res = 0;
	do_cc (amount, coins, 0, res);
	return res;
}

int main()
{
	vector<int> coins {3,5,7,8,9,10,11};
	cout << coinChange (500, coins) << endl;
}
