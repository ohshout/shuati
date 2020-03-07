#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int calculate(string s) {
			cout << s << endl;
        vector<string> postfix = convert(s);
        return eval(postfix);
    }
    
    vector<string> convert (string s) {
        vector<string> postfix;
        stack<char> ops;
        int num = 0;
        int num_processing = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
                num_processing = 1;
            } else if (s[i] == ' ') {
                continue;
            } else {
                //s[i] must be operation
                //push num into postfix first
								if (num_processing) {
									postfix.push_back(to_string(num));
									num = 0;
									num_processing = 0;
								}
                if (ops.empty() || s[i] == '(') {
                    //unconditionally push op
                    ops.push(s[i]);
                } else if (s[i] == ')') {
                    //pop ops from the stack until we encounter '('
                    while (ops.top() != '(') {
                        postfix.push_back(string(1, ops.top()));
                        ops.pop();
                    }
                    ops.pop(); //remove '('
                } else {
                    //s[i] is '+' or '-'
                    //pop out all ops on the stack unitl empty or encoutering '('
                    while (!ops.empty() && ops.top() != '(') {
                        postfix.push_back(string(1, ops.top()));
                        ops.pop();
                    }
                    ops.push(s[i]);
                }
            }
        }
        if (num_processing)
            postfix.push_back(to_string(num));
        while (!ops.empty()) {
            postfix.push_back(string(1, ops.top()));
            ops.pop();
        }
        
        return postfix;
    }
    
    int eval (vector<string> postfix) {
        stack<int> S;
        for (string s: postfix) {
            cout << s  << " ";
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
                }
            }
        }
        return S.top();
    }
};    

int main()
{
	Solution s;
	cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << endl;
}
