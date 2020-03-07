#include <bits/stdc++.h>

using namespace std;


class LogSystem {
	using Day = set<pair<string, int>>;
	using Month = vector<Day>;
	using Year = vector<Month>;

	public:
		LogSystem() : storage(18, Year(12, Month(31))) {}

		//"2017:01:01:23:59:59"
		void getTokens(string & timestamp, int & y, int & m, int & d) {
			y = stoi(timestamp.substr(0, 4));

			m = stoi(timestamp.substr(5,2));

			d = stoi(timestamp.substr(8, 2));

			timestamp = timestamp.substr(11);
		}

		void put(int id, string timestamp) {
			int y, m, d;
			getTokens(timestamp, y, m, d);

			storage[y-2000][m][d].insert(make_pair(timestamp, id));
		}

		//"23:59:59"
		vector<int> retrieve(string s, string e, string gra) {
			vector<int> res;
			int sy, ey, sm, em, sd, ed;

			getTokens(s, sy, sm, sd);
			getTokens(e, ey, em, ed);

			for (int y = sy; y <= ey; y++) {
				auto & year = storage[y-2000];
				for (int m = sm; m <= em; m++) {
					auto & mon = year[m];
					for (int d = sd; d <= ed; d++) {
						set<pair<string, int>> & day = mon[d];
						// traverse set
						string ts, te;

						if (gra == "Hour") {
							ts = s.substr(0,3) + "00:00";
							te = e.substr(0,3) + "59:59";
						} else if (gra == "Minute") {
							ts += s.substr(0,6) + "00";
							te += e.substr(0,6) + "59";
						} else {
                ts = s;
                te = e;
            }

						for (auto it = day.begin(); it != day.end(); it++) {
							if (gra == "Year" || gra == "Month" || gra == "Day") {
								res.push_back(it->second);
							} else {
								if (it->first >= ts && it->first <= te) {
									res.push_back(it->second);
								} else if (it->first > te) {
									break;
								}
							}
						}
					}
				}
			}

			return res;
		}

		vector<Year> storage;
};

int main()
{
	LogSystem ls;
	//ls.put(1, "2017:01:01:23:59:59");
	//ls.put(2, "2017:01:01:22:59:59");
	//ls.put(3, "2016:01:01:00:00:00");
	//ls.put(1,"2017:01:01:23:59:59");
	//ls.put(2,"2017:01:02:23:59:59");
	//auto v = ls.retrieve("2017:01:01:23:59:59", "2017:01:02:23:59:59","Minute");

	ls.put(1,"2017:01:01:23:59:59");
	ls.put(2,"2017:01:02:23:59:59");
	auto v = ls.retrieve("2017:01:01:23:59:58","2017:01:02:23:59:58","Second");

	for (int val : v) {
		cout << val << endl;
	}
}

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(s,e,gra);
 */
