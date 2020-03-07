#include <bits/stdc++.h>

using namespace std;

class Solution {
	struct pqItem {
		int val;
		int row;
		int col;
		pqItem (int v, int r, int c) : val(v), row(r), col(c) {}
		//bool operator< (const pqItem& o) const {
		//	//mimic greater() to get a min-heap
		//	return val > o.val;
		//}
	};

	struct compareItem {
		bool operator() (pqItem a, pqItem b) {
			return a.val > b.val;
		}
	};

	public:
		int kthSmallest(vector<vector<int>>& matrix, int k) {
			vector<int> res;
			priority_queue<pqItem, vector<pqItem>, compareItem> pq;
			for (int i = 0; i < matrix.size(); i++) {
				pq.push({matrix[i][0], i, 0});
			}

			while (!pq.empty()) {
				auto item = pq.top();
				pq.pop();
				res.push_back(item.val);
				if (res.size() == k)
					return item.val;
				int r = item.row, c = item.col;
				c++;
				if (c < matrix[0].size())
					pq.push({matrix[r][c], r,  c});
			}
		}
};

int main()
{
	vector<vector<int>> m { { 1,  5,  9}, {10, 11, 13}, {12, 13, 15}};
	Solution s;
	cout << s.kthSmallest(m, 8) << endl;
}


