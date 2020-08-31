#include <bits/stdc++.h>

using namespace std;

 // This is the interface that allows for creating nested lists.
 // You should not implement it, or speculate about its implementation
 class NestedInteger {
   public:
     // Return true if this NestedInteger holds a single integer, rather than a nested list.
     bool isInteger() const {
			 return isint;
		 }
 
     // Return the single integer that this NestedInteger holds, if it holds a single integer
     // The result is undefined if this NestedInteger holds a nested list
     int getInteger() const {
			 return val_;
		 }
 
     // Return the nested list that this NestedInteger holds, if it holds a nested list
     // The result is undefined if this NestedInteger holds a single integer
     const vector<NestedInteger> &getList() const {
			 return v_;
		 }


		 NestedInteger(int val) : val_(val), isint(true) {}
		 NestedInteger(vector<NestedInteger> & v) : v_(v), isint(false) {}

	 private:
		 vector<NestedInteger> v_;
		 int val_;
		 bool isint;
 };
 

class NestedIterator {
public:
    using Iterator = vector<NestedInteger>::iterator;
    
    stack<Iterator> start, end;
    NestedIterator(vector<NestedInteger> &nestedList) {
				start.push(nestedList.begin());
				end.push(nestedList.end());
    }
    
    int next() {
				while(1) {
					Iterator topS = start.top();
					Iterator & topE = end.top();

					//topS++;
					start.top()++;

					if (start.top() == topE) {
						start.pop();
						end.pop();
					}

					if (topS->isInteger()) {
						return topS->getInteger();
					} else {
            auto new_ni = topS->getList();
						start.push(new_ni.begin());
						end.push(new_ni.end());
					}
				}
    }
    
    bool hasNext() {
        return !start.empty();
    }
};

int main()
{
	NestedInteger n1(1);
	NestedInteger n2(2);
	vector<NestedInteger> v{n1, n2};
	NestedInteger n3(v);

	vector<NestedInteger> v2;
	v2.push_back(n3);

  NestedIterator i(v2);

  while (i.hasNext()) cout << i.next() << " ";
}


