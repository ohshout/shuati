#include <bits/stdc++.h>

using namespace std;

class StringIterator {
public:
    StringIterator(string compressedString) {
      str = compressedString;
      count = 0;
    }
    
    char next() {
      if (count > 0) {
        count--;
        return letter;
      } else if (str=="") {
        return ' ';
      } else {
        letter = str[0];
        str = str.substr(1);
        count = stoi(str);
        str = str.substr(to_string(count).size());
        count--;
        //cout << count << " " << letter << " " << str << endl;
        return letter;
      }
    }
    
    bool hasNext() {
      if (str == "" && count == 0)
        return false;
      else
        return true;
    }
  
private:
  string str;
  int count;
  char letter;
};


int main()
{
	string compressedString = "L1e2t1C1o1d1e1";
	StringIterator obj = StringIterator(compressedString);
	cout << obj.next() << endl;
	cout << obj.next() << endl;
	cout << obj.next() << endl;
	cout << obj.next() << endl;
	cout << obj.next() << endl;
	cout << obj.next() << endl;
	cout << obj.hasNext() << endl;
	cout << obj.next() << endl;
	cout << obj.hasNext() << endl;
}
