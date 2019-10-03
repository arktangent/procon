#include <bits/stdc++.h>

using namespace std;

#define int long long
// #define double long double
#define FOR(i, a, b) for(ll i = (a); i < (b); ++i)
#define FORR(i, a, b) for(ll i = (a); i > (b); --i)
#define REP(i, n) for(ll i = 0; i < (n); ++i)
#define REPR(i, n) for(ll i = n; i >= 0; i--)
#define FOREACH(x, a) for(auto &(x) : (a))
#define VECCIN(x)                                                              \
    for(auto &youso_ : (x)) cin >> youso_
#define bitcnt(x) __builtin_popcount(x)
#define lbit(x) __builtin_ffsll(x)
#define rbit(x) __builtin_clzll(x)
#define SZ(x) ((ll)(x).size())
#define fi first
#define se second
#define All(a) (a).begin(), (a).end()
#define rAll(a) (a).rbegin(), (a).rend()

template <typename T = long long> inline T IN() {
    T x;
    cin >> x;
    return (x);
}
inline void CIN() {}
template <class Head, class... Tail>
inline void CIN(Head &&head, Tail &&... tail) {
    cin >> head;
    CIN(move(tail)...);
}
#define CCIN(...)                                                              \
    char __VA_ARGS__;                                                          \
    CIN(__VA_ARGS__)
#define DCIN(...)                                                              \
    double __VA_ARGS__;                                                        \
    CIN(__VA_ARGS__)
#define LCIN(...)                                                              \
    ll __VA_ARGS__;                                                            \
    CIN(__VA_ARGS__)
#define SCIN(...)                                                              \
    string __VA_ARGS__;                                                        \
    CIN(__VA_ARGS__)
#define Yes(a) cout << (a ? "Yes" : "No") << "\n"
#define YES(a) cout << (a ? "YES" : "NO") << "\n"
#define Printv(v)                                                              \
    {                                                                          \
        FOREACH(x, v) { cout << x << " "; }                                    \
        cout << "\n";                                                          \
    }
template <typename T = string> inline void eputs(T s) {
    cout << s << "\n";
    exit(0);
}
template <typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val) {
    std::fill((T *)array, (T *)(array + N), val);
}

template <typename T> using PQG = priority_queue<T, vector<T>, greater<T>>;
template <typename T> using PQ = priority_queue<T>;

typedef long long ll;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef pair<ll, ll> PL;
typedef vector<PL> VPL;
typedef vector<bool> VB;
typedef vector<double> VD;
typedef vector<string> VS;

const int INF = 1e9;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
const ll LINF = 5e18;
// const double PI = atan(1.0) * 4.0;
const ll dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const ll dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
#define PI 3.141592653589793238

ll N, M;
ll G[701][701];
ll col[701];
bool dp[701];
ll cnum[2];
bool bipartite = true;

void dfs(ll now, ll c) {
    col[now] = c;
    cnum[c]++;
    REP(to, N) {
        if(to == now || !G[now][to]) continue;
        if(col[to] == -1)
            dfs(to, c ^ 1);
        else if(col[to] != c ^ 1)
            bipartite = false;
    }
}

signed main() {
    cin >> N >> M;
    REP(i, N) REP(j, N) G[i][j] = 1;
    REP(i, M) {
        LCIN(A, B);
        A--, B--;
        G[A][B] = 0, G[B][A] = 0;
    }
    Fill(col, -1);
    VPL cnums;
    REP(i, N) {
        if(col[i] != -1) continue;
        Fill(cnum, 0);
        dfs(i, 0);
        cnums.emplace_back(cnum[0], cnum[1]);
        if(!bipartite) eputs(-1);
    }
    dp[0] = 1;
    REP(i, cnums.size()) REPR(j, N) {
        if(!dp[j]) continue;
        dp[j] = 0;
        dp[j + cnums[i].fi] = 1;
        dp[j + cnums[i].se] = 1;
    }
    ll dif = N, left = -1;
    REP(i, N + 1) {
        if(!dp[i]) continue;
        if(dif > abs(i - (N / 2))) dif = abs(i - (N / 2)), left = i;
    }
    cout << (left - 1) * left / 2 + (N - left - 1) * (N - left) / 2 << "\n";
}
