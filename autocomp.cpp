#include <bits/stdc++.h>

using namespace std;

class AutocompleteSystem {
public:
	struct ComparePair {
		bool operator() (pair<string, int> p1, pair<string, int> p2) {
			if (p1.second > p2.second)
				return true;
			else if (p1.second < p2.second)
				return false;
			else if (p1.first < p2.first)
				return true;
			else
				return false;
		}
	};

	struct TrieNode {
		set<pair<string, int>, ComparePair> top3; //<id, freq>
		vector<TrieNode*> children; /* a - z, ' ' */
		
		TrieNode (): children (27, NULL) {}
	};
	
	AutocompleteSystem(vector<string> sentences, vector<int> times) {
		//init dummy root
		dummy_root = new TrieNode ();
			
		for (int i = 0; i < sentences.size(); i++) {
			string s = sentences[i];
			int freq = times[i];
			//cout << s << " " << freq << endl;
				
			TrieNode * node = dummy_root;
			for (char c: s) {
				int pos = (c >= 'a' && c <= 'z') ? (c-'a') : 26;
				//cout << pos << endl;
				//node = node->children[pos];
				TrieNode * tmp = node->children[pos];
				if (!tmp) {
					tmp = new TrieNode ();
					node->children[pos] = tmp;
				}
				tmp->top3.insert({s, freq});
				//if (tmp->top3.size() > 3) {
				//	//remove the last one
				//	tmp->top3.erase(prev(tmp->top3.end()));
				//}

				node = tmp;
			}
		}

		//init cur
		cur = dummy_root;
		//init input_so_far
		input_so_far = "";
	}

	void save_sentence(string sentence) {
		//cout << sentence << endl;
		TrieNode * node = dummy_root;
		for (char c: sentence) {
			int pos = (c >= 'a' && c <= 'z') ? (c-'a') : 26;
			TrieNode * tmp = node->children[pos];
			if (!tmp) {
				tmp = new TrieNode ();
				node->children[pos] = tmp;
			}
			/* now, insert the sentence to top3 in tmp */
			//auto S = tmp->top3;
			set<pair<string, int>, ComparePair>& S = tmp->top3;
			int flag = 0;
			for (auto it = S.begin(); it != S.end(); it++) {
				if (it->first == sentence) {
					int freq = it->second;
					S.erase(it);
					S.insert({sentence, freq+1});
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				//updated existing one
				node = tmp;
				continue;
			} else {
				//create new entry
				S.insert({sentence, 1});
				//if (S.size() > 3)
				//	S.erase(prev(S.end()));
			}
			node = tmp;
		}
	}
	
	vector<string> input(char c) {
		if (c == '#') {
			//save the sentence
			save_sentence (input_so_far);
			//reset cur
			cur = dummy_root;
			input_so_far = "";
			return {};
		}

		input_so_far.push_back(c);

		if (cur == NULL)
			return {};

		int pos = (c >= 'a' && c <= 'z') ? (c-'a') : 26;
		cur = cur->children[pos];
		if (cur == NULL)
			return {};
		else {
			vector<string> res;
			/***************/
			int count = 0;
			for (auto p: cur->top3) {
				if (count == 3)
					break;
				res.push_back(p.first);
				count++;
			}
			/***************/
			return res;
		}
  }
    
private:
    TrieNode * dummy_root;
		TrieNode * cur;
		string input_so_far;
};

int main()
{
	vector<string> sentences = {"abc", "abbc", "a"};
	vector<int> freq = {3,3,3};
	AutocompleteSystem obj = AutocompleteSystem(sentences, freq);
	vector<string> res = obj.input('b');
	for (string s: res)
		cout << s;
	cout << endl;
	res = obj.input('c');
	for (string s: res)
		cout << s;
	cout << endl;
	res = obj.input('#');
	for (string s: res)
		cout << s;
	cout << endl;
	res = obj.input('b');
	for (string s: res)
		cout << s;
	cout << endl;
}


