#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> Map (10, vector<char>(10, '*'));;

int main()
{
	for (int i = 0; i < Map.size(); i++) {
		for (int j = 0; j < Map[i].size(); j++) {
			cout << Map[i][j] << " ";
		}
		cout << endl;
	}

	srand(time(NULL));
	int startx = rand() % 10;
	int starty = rand() % 10;
	cout << "(" << startx << "," << starty << ")" << endl;

	int offsetx = 0-startx;
	int offsety = 0-starty;
}


