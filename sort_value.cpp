#include <bits/stdc++.h>

using namespace std;


int main()
{
	vector<pair<int, int>> v {{1,2},{2,1},{1,2},{2,1}};
	//sort (v.begin(), v.end(), [](pair<int,int> a, pair<int,int> b)
	//		{ return a.second > b.second;});
	make_heap(v.begin(), v.end());
	unordered_map<int, int> M; // <n, count>
	for (auto v_i: v) {
		M[v_i.first]++;
	}
	for (auto m_i: M)
		cout << m_i.first << " " << m_i.second << endl;
	//for (auto v_i: v) {
	//	cout << v_i.first << " " << v_i.second << endl;
	//}
}


