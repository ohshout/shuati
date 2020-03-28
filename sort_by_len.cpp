#include <bits/stdc++.h>

using namespace std;

int main()
{
	struct strCmp {
		bool operator()(string const & str1, string const & str2) {
			return str1.size() < str2.size();
		}
	};

	vector<string> words{"am", "China", "I", "from"};
	sort(words.begin(), words.end(), strCmp());

	for (auto & s : words) {
		cout << s << endl;
	}
}


