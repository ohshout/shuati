#include <bits/stdc++.h>

using namespace std;

using Day = set<pair<string, int>>;
using Month = vector<Day>;
using Year = vector<Month>;

class Log {
	public:

};


int main()
{
		Log l;
		int y = 2000, m = 1, d = 2;
		string timestamp = "hello";
		int id = 2;
		l.storage[y-2000][m][d].insert(make_pair(timestamp, id));
}

