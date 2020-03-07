#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    struct pq_item {
        string word_;
        int freq_;
        pq_item(string word, int freq) : word_(word), freq_(freq) {} 
        
				// less -> max heap
				// if you want to put l after r
				// return true
        friend bool operator<(pq_item const & l, pq_item const & r) {
            if (l.freq_ > r.freq_) {
                return true;
            } else if (l.freq_ < r.freq_) {
                return false;
            } else if (l.word_.compare(r.word_) < 0) {
                return true;
            } else {
                return false;
            }
        }
    };
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for (string & w: words) {
            if (freq.find(w) == freq.end()) {
                freq.insert({w, 0});
            } else {
                freq[w]++;
            }
        }
        
        priority_queue<pq_item> pq;
        
        for (auto it = freq.begin(); it != freq.end(); it++) {
            pq.push(pq_item{it->first, it->second});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        vector<string> res (k);
        while (!pq.empty()) {
            res.push_back(pq.top().word_);
            pq.pop();
        }
        
        return res;
    }
};

int main()
{
	Solution sol;
	vector<string> v {"i", "love", "leetcode", "i", "love", "coding"};

	sol.topKFrequent(v, 2);
}

