class LRUCache {
public:
    struct cacheVal {
        int val;
        list<int>::iterator it;
        cacheVal() = default; 
        cacheVal(int val_, list<int>::iterator it_) : val(val_), it(it_) {}
    };
    
    unordered_map<int, cacheVal> cache; // key -> cacheVal
    list<int> lru; // key
    int cap_;
    int sz = 0;
    
    LRUCache(int capacity) {
        cap_ = capacity;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        } else {
            cacheVal &val = cache[key];
            // before return, promote the key
            promote(key, val);
            
            return val.val;
        }
    }
    
    void put(int key, int value) {
        if (cache.find(key) == cache.end()) {
            if (sz == cap_) {
                // remove the head of the lru
                int rkey = lru.front();
                cache.erase(rkey);
                lru.pop_front();
                sz--;
            }
        } else {
            // update existing key
            promote(key, cache[key]);
        }
        
        // insert the new key/value
        lru.push_back(key);
        auto it = lru.end();
        --it;

        cache[key] = cacheVal(value, it);
        sz++;
    }
    
    void promote(int key, cacheVal & val) {
        // remove it from the original place
        lru.erase(val.it);
        
        // put it to the end of the list
        lru.push_back(key);
    }
};

int main()
{

  LRUCache* obj = new LRUCache(capacity);
  int param_1 = obj->get(key);
  obj->put(key,value);
}

/**
 * Your LRUCache object will be instantiated and called as such:
 */
