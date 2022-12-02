#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.size()/16; i++)
        for (int j = 7; j >= 0; j--)
            cout << s[i*16 + j * 2] << s[i*16 + j * 2 + 1];
}