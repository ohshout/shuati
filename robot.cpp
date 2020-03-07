#include <bits/stdc++.h>

using namespace std;

class Robot {
public:
	void set_map(vector<vector<int>>& grid) {Map = grid;}
	void set_init_pos_dir(pair<int,int> pos) {
		cur_pos = pos;
		cur_dir = {1,0};
	}

	//clean method
	int count = 0;
	void clean() {count++;}
	int get_cleaned() {return count;}

	//turn right
	void turnRight(int k) {
		int i;
		for (i = 0; i < unit_dir.size(); i++)
			if (unit_dir[i] == cur_dir)
				break;
		k = k%4;
		i -= k;
		i = ((i%4)+4)%4;
		cur_dir = unit_dir[i];
	}

	//turn left
	void turnLeft(int k) {
		int i;
		for (i = 0; i < unit_dir.size(); i++)
			if (unit_dir[i] == cur_dir)
				break;
		k = k%4;
		i += k;
		i = i%4;
		cur_dir = unit_dir[i];
	}

	//move forward if possible
	bool move() {
		int r = cur_pos.first + cur_dir.first;
		int c = cur_pos.second + cur_dir.second;

		if (r < 0 || r >= Map.size())
			return false;
		if (c < 0 || c >= Map[0].size())
			return false;
		if (Map[r][c] == 0)
			return false;
		else {
			cur_pos.first = r;
			cur_pos.second = c;
			return true;
		}
	}

private:
	vector<vector<int>> Map;
	pair<int,int> cur_dir;
	pair<int,int> cur_pos;
	vector<pair<int, int>> unit_dir {{1,0}, {0,1}, {-1,0}, {0,-1}}; //turning 90 degree left with increasing index
};

class Solution {
public:
    void set_up_test_frame(vector<vector<int>>& grid) {
				int r = 1, c = 3;
				rob.set_map(grid);
				rob.set_init_pos_dir({r, c});
    }
    
    int explore () {
        stack<pair<int, int>> S;
				set<pair<int,int>> visited;

				//init original position
				cur_pos = {0,0};
        S.push(cur_pos); //always set starting point to (0,0)
				//init original direction, always init to be pointing right
				cur_dir = {1,0};
        
        while(!S.empty()) {
            auto p = S.top();
            //S.pop(); //we only pop when backtracking
            
            int row = p.first, col = p.second;
						cout << "{" << row << " " << col << "}" << endl;
            if (visited.find({row, col}) == visited.end()) {
							//first time to this cell, clean it
              rob.clean();
							//mark it cleaned
              visited.insert({row, col});
            }
           
						//dfs part:
						//try every neighbor cell, if it's not out of boundary, not obstacle, and we've never been there,
						//we move to that neighbor cell.
						//if there's no neighbor cell to move to, we backtrack to the previous cell
						vector<pair<int, int>> v {{row-1, col}, {row+1, col}, {row, col-1}, {row, col+1}}; //{up, down, left, right}
						int i;
						for (i = 0; i < v.size(); i++) {
							auto new_pos = v[i];
							if (visited.find(new_pos) == visited.end()) {
								//if we've never been to this cell, try moving to it and check out
								if (move_to (new_pos)) {
									S.push(new_pos);
									break;
								}
							}
						}

						//no neighbor to go
						//we backtrack
						if (i == v.size()) {
							S.pop();
							if (!S.empty()) {
								cout << "returning" << endl;
								move_to (S.top());
							}
						}
        }
    
        return rob.get_cleaned();
    }
	
private:
		pair<int, int> cur_dir;
		pair<int, int> cur_pos;
		Robot rob;

		//move () only moves forward, move_to() is a wrapper that specifies destination
		//so that the robot will turn first then move forward
		bool move_to (pair<int,int> new_pos) {
			//can only move to neighbor cell
			if (abs(cur_pos.first - new_pos.first) + abs(cur_pos.second - new_pos.second) != 1)
				cout << "error!!" << endl;

			//turn to that direction
			map<pair<int, int>, int> unit_dir {{{1,0}, 0}, {{0,1}, 1}, {{-1,0},2}, {{0,-1},3}}; //<{dir.x, dir.y}, k for turnLeft>
			pair<int, int> new_dir = {new_pos.first - cur_pos.first, new_pos.second - cur_pos.second};
			int k = unit_dir[new_dir] - unit_dir[cur_dir];
			if (k > 0) rob.turnLeft (k);
			else rob.turnRight (abs(k));
			//update cur_dir
			cur_dir = new_dir;

			//now try moving
			if (rob.move()) {
				//success, update pos
				cur_pos = new_pos;
				return true;
			} else
				return false;
		}
};

int main()
{
	Solution s;
	vector<vector<int>> Map {{0,1,1,0,1},{1,1,1,1,1},{0,1,0,1,1},{0,0,1,1,1}};
	s.set_up_test_frame(Map);
	cout << s.explore() << endl;
}
