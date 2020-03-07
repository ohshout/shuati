#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	vector<int> v {1,1,1};

	vector<string> res;

	queue<pair<string, vector<int>>> Q;

	for (int i = 0; i < v.size(); i++) {
		v[i] = 0;
		Q.push({to_string(i), v});
		v[i] = 1;
	}

	while (!Q.empty()) {
		auto p = Q.front();
		Q.pop();
		string s = p.first;
		if (s.size() == 3) {
			res.push_back(s);
		} else {
			vector<int> v1 = p.second;
			for (int i = 0; i < v1.size(); i++) {
				if (v1[i]) {
					v1[i] = 0;
					Q.push({s+to_string(i), v1});
					v1[i] = 1;
				}
			}
		}
	}

	for (string s: res)
		cout << s << endl;

	return 0;
}

