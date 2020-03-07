#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        vector<string> postfix;
        int num = 0;
        int num_processing = 0;
        char op; 
        stack<char> ops;
    
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ')
                continue;
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
                num_processing = 1;
            } else {
								op = s[i];
                //s[i] is operation
                //push num into postfix first
                postfix.push_back(to_string(num));
                num = 0;
                num_processing = 0;
                if (ops.empty()) {
                    ops.push(op);
                } else {
                    //pop all ops on the stack, that have higher or equal precedence to op
                    //so if op is '+' or '-', pop all ops on the stack
                    //if op is '*' or '/', pop '*' or '/' only
                    if (op == '+' or op == '-') {
                        while (!ops.empty()) {
                            postfix.push_back(string(1, ops.top()));
                            ops.pop();
                        }
                    } else {
                        while (!ops.empty() && (ops.top() == '/' or ops.top() == '*')) {
                            postfix.push_back(string(1,ops.top()));
                            ops.pop();
                        }
                    }
                    //push the current op onto the stack
                    ops.push(op);
                }
            }
        }
        
        if (num_processing)
            postfix.push_back(to_string(num));
        
        //pop all ops on the stack to postfix
        while (!ops.empty()) {
            postfix.push_back(string(1,ops.top()));
            ops.pop();
        }
        
        return eval (postfix);
    }
    
    int eval (vector<string> postfix) {
        stack<int> S;
        for (string s: postfix) {
           // cout << s;
            if (isdigit(s[0]))
                //operands
                S.push(stoi(s));
            else {
                //operations
                int n2 = S.top();
                S.pop();
                int n1 = S.top();
                S.pop();
                switch (s[0]) {
                    case '+':
                        S.push(n1+n2);
                        break;
                    case '-':
                        S.push(n1-n2);
                        break;
                    case '*':
                        S.push(n1*n2);
                        break;
                    case '/':
                        S.push(n1/n2);
                        break;
                }
            }
        }
        return S.top();
    }
};

int main()
{
	Solution s;
	cout << s.calculate("3+2*2") << endl;
}
