#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool canTransform(string start, string end) {
        if (start.size() != end.size())
            return false;
        int i = 0, j = 0;
        while (i < start.size() && j < end.size()) {
            if (start[i] == 'X') {
                i++;
                continue;
            }
            if (end[j] == 'X') {
                j++;
                continue;
            }
            if (start[i] != end[j])
                return false;
						else if (start[i] == 'L' && i < j)
								return false;
						else if (start[i] == 'R' && i > j)
								return false;
            else
                i++, j++;
        }
        
        while (i < start.size()) {
            if (start[i] != 'X')
                return false;
            i++;
        }
        while (j < end.size()) {
            if (end[j] != 'X')
                return false;
            j++;
        }
        return true;
    }
};

int main()
{
	Solution s;
	cout << s.canTransform ("XXXXXLXXXX", "LXXXXXXXXX") << endl;
}
