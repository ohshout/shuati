#include <bits/stdc++.h>

using namespace std;

class base {
public:
	base (int x) : a (x) {};
	virtual int func () {return a;}
	int a;
};

class derived: public base
{
public:
	derived (int x) : base(x), a (5) {};
	int func () {return base::a;}
	int a;
};

int main()
{
	base b = base(2);
	derived d = derived(3);
	base& bref = d;
	derived& dref = d;
	cout << bref.func() << endl;
}


