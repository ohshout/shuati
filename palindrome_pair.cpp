#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct trieNode {
        int idx_;
        vector<trieNode *> children_;
        
        trieNode ()
            : idx_(-1)
            , children_(26, nullptr) 
        {}
    };
    
    void insertStr (trieNode * node, string word, int idx)
    {
        trieNode * tmp = node;
        for (char c : word) {
            if (tmp->children_[c-'0'] == nullptr) {
                tmp->children_[c-'0'] = new trieNode();
            }
            tmp = tmp->children_[c-'0'];
        }
        
        tmp->idx_ = idx;
    }
    
    int searchStr(trieNode * node, string word)
    {
        int i = 0;
        trieNode * tmp = node;
        int idx;
        
        while(i < word.size()) {
            char c = word.at(i);
            
            if (tmp->children_[c-'0'] != nullptr) {
                tmp = tmp->children_[c-'0'];
            } else {
                // start checking i - end
                int l = i, r = word.size()-1;
                
                while(l <= r) {
                    if (word.at(l) != word.at(r)) {
                        return -1;
                    }
                    l++;
                    r--;
                }
                
                return tmp->idx_;
            }
            i++;
        }
        
        // when we reach here, we've finished the word
        return tmp->idx_;
    }
    
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        
        trieNode * root = new trieNode();
        
        //construct Trie
        for (int i = 0; i < words.size(); ++i) {
            insertStr(root, words[i], i);
        }

				cout << "here" << endl;
        
        //now match
        for (int i = 0; i < words.size(); ++i) {
            string word = words.at(i);
            reverse(word.begin(), word.end());
            
            int idx = searchStr(root, word);
            if (idx != -1 && idx != i) {
                res.push_back({i, idx});
                res.push_back({idx, i});
            }
        }
        
        return res;
    }
};

int main()
{
	vector<string> v{"abcd","dcba","lls","s","sssll"};
	Solution sol;
	sol.palindromePairs(v);
}

