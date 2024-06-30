#include <bits/stdc++.h>

// Longest Palindromic Substring

using namespace std;

string longestPalindrome(string s) {
    string str, ret;
    str += "#";
    for (char c : s) {
        str += c;
        str += "#";
    }
    int n = str.size(), maxim = 0, ans = 0;
    vector<int> d(n);
    int l=0, r=-1;
    for (int i=0; i<n; ++i) {
        int k = i>r ? 1 : min(d[l+r-i], r-i+1);
        while (i+k < n && i-k >= 0 && str[i+k] == str[i-k])  ++k;
        d[i] = k;
        if (i+k-1 > r)
            l = i-k+1,  r = i+k-1;
    }
    for (int i = 0; i < n; ++i) {
        if (d[i] > maxim) {
            maxim = d[i];
            ans = i;
        }
    }
    for (int i = ans - maxim + 1; i < ans + maxim; ++i) {
        if (str[i] != '#') {
            ret += str[i];
        }
    }
    return ret;
}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    string input;
    cin >> input;
    cout << longestPalindrome(input);
    return 0;
}
