#include <bits/stdc++.h>

using namespace std;

// inclusive
void maxSumOnLeft(vector<int>& A, vector<int>& res, int len) {
        int sum = 0;
        int to_add = 0, to_remove = 0;
        int max_ = 0;
        
        while(to_add < A.size()) {
            // add to_add in
            sum += A.at(to_add);
            
            // remove to_remove if desired
            if (to_add - to_remove + 1 > len) {
                sum -= A.at(to_remove);
                to_remove++;
            }
            
            if (to_add - to_remove + 1 == len) {
                max_ = std::max(max_, sum);
                res.at(to_add) = max_;
            }
            
            to_add++;
        }
        
        return;
    }

// inclusive
    void maxSumOnRight(vector<int>& A, vector<int>& res, int len) {
        int sum = 0;
        int to_add = A.size()-1, to_remove = A.size()-1;
        int max_ = 0;
        
        while(to_add >= 0) {
            // add to_add in
            sum += A.at(to_add);
            
            // remove to_remove if desired
            if (to_remove - to_add + 1 > len) {
                sum -= A.at(to_remove);
                to_remove--;
            }
            
            if (to_remove - to_add + 1 == len) {
                max_ = std::max(max_, sum);
                res.at(to_add) = max_;
            }
            
            to_add--;
        }
        
        return;
    }

int main()
{
	vector<int> v{0, 6, 5, 2, 2, 5, 1, 9, 4};
	vector<int> res(v.size(), -1);
	vector<int> res2(v.size(), -1);
	maxSumOnLeft(v, res, 2);
	maxSumOnRight(v, res2, 1);

	for (int n : v) {
		cout << n << " ";
	}
	cout << endl;

	for (int n : res) {
		cout << n << " ";
	}
	cout << endl;

	for (int n : res2) {
		cout << n << " ";
	}
	cout << endl;
}
