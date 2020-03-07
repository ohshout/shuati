#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct wall {
        int x_;
        bool isEnd_;
        int h_;
        wall(int x, bool isEnd, int h) : x_(x), isEnd_(isEnd), h_(h) {}
    };
    
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<wall> walls;
        
        for(int i = 0; i < buildings.size(); i++) {
            auto & b = buildings[i];
            walls.emplace_back(b[0], false, b[2]);
            walls.emplace_back(b[1], true, b[2]);
        }
        
        sort(walls.begin(), walls.end(), [](wall a, wall b) {
            if (a.x_ == b.x_) {
                return !a.isEnd_;
            } else {
                return a.x_ < b.x_;
            }
        });
        
        map<int,int> block; //<height, freq>
        vector<vector<int>> res;
        
        for (auto & w : walls) {
            int old_height = block.begin()->first;
            
            if (!w.isEnd_) {
                if (block.find(w.h_) == block.end()) {
                    if (w.h_ > old_height) {
                        res.push_back({w.x_, w.h_});
                    }
                    block.insert({w.h_, 1});
                } else {
                    block[w.h_]++;
                }
            } else {
                if (block[w.h_] == 1) {
                    block.erase(w.h_);
                    if (w.h_ == old_height) {
                        // deleted the last highest
                        if (block.size() == 0) {
                            res.push_back({w.x_, 0});
                        } else {
                            res.push_back({w.x_, block.begin()->first});
                        }
                    }
                } else {
                    block[w.h_]--;
                }
            }
        }
        
        return res;
    }
};

int main()
