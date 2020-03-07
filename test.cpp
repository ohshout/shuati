#include <bits/stdc++.h>

using namespace std;

vector<int> func()
{
	return {1,2};
}

void func(vector<int>& v)
{
	for (int v_i: v)
		cout << v_i << endl;
}

struct ComparePair {
	bool operator() (pair<int, int> p1, pair<int, int> p2) {
		if (p1.second > p2.second)
			return true;
		else if (p1.second < p2.second)
			return false;
		else if (p1.first < p2.first)
			return true;
		else
			return false;
	}
};

int main()
{
	/*
	vector<int> S;
	S.push_back(1);
	S.push_back(3);
	S.push_back(9);
	S.push_back(29);
	S.push_back(4);
	S.push_back(44);
	vector<int> v;
	v = S;
	v.push_back(434);
	for (int i: S)
		cout << i << endl;
		*/

	//vector<string> v;
	//string s (1,'a');
	//v.push_back(string(1,'a'));
	//int N = 3;
	//vector<vector<vector<int>>> M (N, vector<vector<int>>(N, vector<int>(N, -1)));
	//vector<vector<int>> M (3, vector<int> (2, -1));
	//cout << M[1][2] << endl;
	//string s = "dfdf";
	//s[0] = 'a';
	//cout << s << endl;
	//vector<vector<int>> v (0, vector<int> (0));
	unordered_set<vector<int>> M;
}























