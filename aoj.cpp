#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define FORR(i, a, b) for(int i = (a); i > (b); --i)
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPR(i, n) for(int i = n; i >= 0; i--)
#define FOREACH(x, a) for(auto &(x) : (a))
#define VECCIN(x)                                                              \
    for(auto &youso_ : (x)) cin >> youso_
#define mp make_pair
#define bitcnt __builtin_popcount
#define All(a) (a).begin(), (a).end()
template <typename T = long long> inline T IN() {
    T x;
    cin >> x;
    return (x);
}
// inline void CIN() {}
// template <class Head, class... Tail>
// inline void CIN(Head &&head, Tail &&... tail) {
//     cin >> head;
//     CIN(move(tail)...);
// }
// CIN(__VA_ARGS__)
// CIN(__VA_ARGS__)
// CIN(__VA_ARGS__)
// #define Yes(a) cout << (a ? "Yes" : "No") << "\n"
// #define YES(a) cout << (a ? "YES" : "NO") << "\n"

typedef long long ll;
typedef vector<int> V;
typedef vector<ll> VL;
typedef pair<int, int> P;
typedef pair<ll, ll> PL;
typedef priority_queue<int> PQ;
// typedef priority_queue<int, V, greater<int>> PQG;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

ll N;
VL p;

int main() {
    cin >> N;
    p.resize(N);
    VECCIN(p);
    int ans = 1e9;
    for(int k = 0; k <= 3; ++k) {
        int nans = k;
        int from = k;
        for(int i = 0; i < N; ++i) {
            int plus = max(0, (int)p[i] - from);
            nans += (i == N - 1 ? 1 : 2) * max(0, plus);
            from = plus;
        }
        ans = min(ans, nans);
    }
    cout << ans << endl;
    return 0;
}
