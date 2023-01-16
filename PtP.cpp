// S.A.Moosavi
// A.M.Ascarieh
#include <bits/stdc++.h>

using namespace std;

int main() {
    stack<string> a;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == ')') {
            string b = a.top();
            a.pop();
            b += c;
            a.push(b);
        } else if (c == '(') {
            string b;
            b += c;
            a.push(b);
        } else if (c <= 'z' && c >= 'a') {
            string b;
            if (!a.empty() && a.top() == "(")
                b += a.top();
            b += c;
            a.push(b);
        } else {
            string b = a.top();
            a.pop();
            string d = a.top();

            d += c;
            d += b;
            a.pop();
            a.push(d);
        }
    }
    cout << a.top() << endl;
}