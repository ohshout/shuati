#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //the basic idea is very simple:
        //to minimize the total time,
        //always pick the runnable task with the most pending jobs.
        //The intuition is that, if we don't do this,
        //It's more likely to have multiple jobs of the
        //same task pending towards the end and each of them will cause the CPU
        //to pause for n-1 time units.
        
        //find the initial number of pending jobs for each task
        unordered_map<char, int> M;
        for (char t: tasks) {
            M[t]++;
        }
        
        //dump those tasks into priority queue, decreasing order of # of pending jobs
        //notice that I don't really need the task name
        priority_queue<int> runQ;
        for (auto m: M) {
            runQ.push(m.second);
        }
        
        
        queue<pair<int,int>> waitQ; //<time_exec'ed, # of pending jobs>
        //start simulation:
        //every CPU cycle:
        //1. check waitQ, remove ready tasks and put them into runQ
        //2. try fetching one task from the runQ.
        //If runQ is empty, sleep for a period of time until there will be task ready
        //If runQ is not empty, remove the first task, decrement its pending jobs, update
        //its exection timestamp and insert to the tail of the waitQ
        //3. increment curTime
        int curTime = 0;
        while (1) {
            //move ready tasks from waitQ to runQ
            while (waitQ.size()) {
                auto p = waitQ.front();
                if (curTime - p.first > n) {
                    //task ready
                    waitQ.pop();
                    runQ.push(p.second);
                } else
                    break;
            }
            
            //fetch task from runQ
            if (!runQ.size()) {
                int n = runQ.top();
                runQ.pop();
                //execute current task
                n--;
                if (n) waitQ.push({curTime, n});
            }
            
            if (!waitQ.size() && !runQ.size())
                break;
            
            //TODO 
            curTime++;
        }
        
        return curTime;
    }
};


int main()
{
	Solution s;
	vector<char> tasks {'A','A','A','B','B','B'};
	cout << s.leastInterval (tasks, 2) << endl;
}


