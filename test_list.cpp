#include <list>
#include <iostream>


using namespace std;

int main()
{
	list<int> l {1,2,33,4,5};
	auto e = l.end();
	cout << *(e-1) << endl;
}
