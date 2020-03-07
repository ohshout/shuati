#include <iostream>
#include <vector>

using namespace std;

class mypq {
	public:
		void insert(int i);
		int removeMax ();
	private:
		int last_idx = 0;
		vector<int> _mypq {-1};
		void swap (int a, int b) {
			int tmp = _mypq[a];
			_mypq[a] = _mypq[b];
			_mypq[b] = tmp;
		}
};

void mypq::insert(int i) {
	_mypq.push_back(i);
	last_idx++;
	int idx = last_idx;
	//swap with parent if parent is samller
	while (idx != 1) {
		if (_mypq[idx/2] < _mypq[idx]) {
			swap(idx/2, idx);
			idx = idx/2;
		} else
			break;
	}
}

int mypq::removeMax () {
	int maxI = _mypq[1];
	_mypq[1] = _mypq[last_idx];
	_mypq.pop_back();
	last_idx--;
	int idx = 1;
	while (idx * 2 <= last_idx) {
		if (idx*2 + 1 <= last_idx) {
			if (_mypq[idx*2] > _mypq[idx*2+1]) {
				swap(idx, idx*2);
				idx = idx*2;
			} else {
				swap(idx, idx*2+1);
				idx = idx*2+1;
			}
		} else {
			swap(idx, idx*2);
			idx = idx*2;
		}
	}
	return maxI;
}

int main()
{
	mypq pq = mypq();
	pq.insert(15);
	pq.insert(1);
	pq.insert(2);
	pq.insert(23);
	pq.insert(34);
	pq.insert(5);
	pq.insert(33);
	pq.insert(12);
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
	cout << pq.removeMax() << endl;
}
