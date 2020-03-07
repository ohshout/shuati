#include <queue>
#include <iostream>

using namespace std;


struct Person
{
	int age;
	Person(int _age) : age(_age) {}

	// less -> max_heap
	// returning true puts l behind r in a max heap
	friend bool operator<(Person const & l, Person const & r) {
		return l.age < r.age;
	}
};

int main()
{
	priority_queue<Person> pq;

	pq.push(Person(25));
	pq.push(Person(24));
	pq.push(Person(26));

	while(!pq.empty()) {
		cout << pq.top().age << endl;
		pq.pop();
	}

	return 0;
}
