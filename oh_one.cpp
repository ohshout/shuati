#include <bits/stdc++.h>

using namespace std;

class AllOne {
    struct ListNode {
        string key;
        int val;
        ListNode * next;
        ListNode * prev;
        
        ListNode(string k, int value) : 
            key(k), val(value), next(nullptr), prev(nullptr) {}
    };
    
    unordered_map<string, ListNode*> K;
    unordered_map<int, ListNode*> V;
    int max_val = 0;
    int min_val = INT_MAX;
    
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    // helpers
    void insert_node_to_V (ListNode * node) {
        int val = node->val;
				cout << "inserting " << node->key << " to val: " << val << endl;
        
        if (V.find(val) == V.end()) {
            V.insert({val, node});
        } else if (V[val] == nullptr) {
            V[val] = node;
        } else {
            ListNode * cur_head = V[val];
            node->next = cur_head;
            cur_head->prev = node;
            V[val] = node;
        }
    }
    
    void remove_node_from_V(ListNode * node) {
        int val = node->val;
        if (node->prev == nullptr && node->next == nullptr) {
            // this is the last node of 'val'
					  cout << "setting entry: " << val << " to null" << endl;
            V[val] = nullptr;
        } else {
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            } else {
							  V[val] = node->next;
						}

            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }
        }
    }
    
    void update_min_max_inc(int old_val, int new_val) {
        // unconditionally update max_val
        max_val = std::max(new_val, max_val);
        
        // we might need to update min_val:
        // 1. old_val used to be the min_val and we removed the last of it
        // 2. a new comer
        if (new_val == 1 || (old_val == min_val && V[old_val] == nullptr)) {
            min_val = new_val;
        }
    }
    
    void update_min_max_dec(int old_val, int new_val) {
        if (new_val != 0) {
            // unconditionally update min_val
            min_val = std::min(new_val, min_val);
            
            // we might need to update max_val
            if (old_val == max_val && V[old_val] == nullptr) {
                max_val = new_val;
            }
        } else if (V[old_val] == nullptr) {
            // we have removed all the nodes
            // reset min and max
            max_val = 0;
            min_val = INT_MAX;
        }
    }
        
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (K.find(key) == K.end()) {
            ListNode * node = new ListNode(key, 1);
            insert_node_to_V(node);
            K.insert({key, node});
            update_min_max_inc(0, 1);
        } else {
            ListNode * node = K[key];
            int cur_val = node->val;
            
            // remove the old node
            remove_node_from_V(node);
            delete node;
            
            // insert a new node
            ListNode * new_node = new ListNode(key, cur_val+1);
            insert_node_to_V(new_node);
            update_min_max_inc(cur_val, new_node->val);
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (K.find(key) == K.end()) {
            // If the key does not exist, this function does nothing.
            return;
        }
        
        ListNode * node = K[key];
        int orig_val = node->val;
        
        // remove the old node
        remove_node_from_V(node);
        delete node;
        
        int new_val = orig_val - 1;
				cout << key << " has new val: " << new_val << endl;
        if (new_val == 0) {
            // If Key's value is 1, remove it from the data structure.
					cout << "removing key: " << key << endl;
            K.erase(key);
        } else {
            // insert a new node
            ListNode * new_node = new ListNode(key, new_val);
            insert_node_to_V(node);
        }
        update_min_max_dec(orig_val, new_val);
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (max_val == 0) {
            return "";
        } else {
            return V[max_val]->key;
        }
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
				cout << min_val << endl;
        if (min_val == INT_MAX) {
            return "";
        } else {
            return V[min_val]->key;
        }
    }
};

int main()
{
  AllOne* obj = new AllOne();
  obj->inc("a");
  obj->inc("b");
  obj->inc("b");
  obj->inc("c");
  obj->inc("c");
  obj->inc("c");
  obj->dec("b");
  obj->dec("b");
  string param_3 = obj->getMinKey();
	cout << param_3 << endl;
  obj->dec("a");
  string param_4 = obj->getMinKey();
	cout << param_4 << endl;
  string param_5 = obj->getMaxKey();
	cout << param_5 << endl;
}

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
