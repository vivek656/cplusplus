#include <bits/stdc++.h>
using namespace std;

long long x, y;
long long mn, p, q;

void check(long long tp, long long tq)
{
    if ((tp & tq) == 0 && abs(tp - x) + abs(tq - y) < mn) {
        mn = abs(tp - x) + abs(tq - y);
        p = tp;
        q = tq;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> x >> y;

        mn = 1e18; 

        if ((x & y) == 0) {
            cout << x << " " << y << endl;
            continue;
        }

        long long common = (x & y);
        int msb = 63 - __builtin_clzll(common); 

        check((x >> msb << msb) + (1LL << msb), y);
        check(x, (y >> msb << msb) + (1LL << msb));
        check(x >> msb << msb, (y >> msb << msb) - 1);
        check((x >> msb << msb) - 1, y >> msb << msb);

        cout << p << " " << q << endl;
    }
}
