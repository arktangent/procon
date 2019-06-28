#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FOR(i, a, b) for(ll i = (a); i < (b); ++i)
#define FORR(i, a, b) for(ll i = (a); i > (b); --i)
#define REP(i, n) for(ll i = 0; i < (n); ++i)
#define REPR(i, n) for(ll i = n; i >= 0; i--)
#define FOREACH(x, a) for(auto &(x) : (a))
#define VECCIN(x)                                                              \
    for(auto &youso_ : (x)) cin >> youso_
#define bitcnt __builtin_popcount
#define SZ(x) ((ll)(x).size())
#define fi first
#define se second
#define All(a) (a).begin(), (a).end()
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
#define CINT(...)                                                              \
    int __VA_ARGS__;                                                           \
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
typedef unsigned long long ul;
typedef vector<ll> VL;
typedef pair<ll, ll> PL;

const int INF = 1e9;
const int MOD = 1e9 + 7;
const double PI = atan(1.0) * 4.0;
// const int MOD = 998244353;
const ll LINF = 9e18;
const ll dx[] = {1, 0, -1, 0};
const ll dy[] = {0, 1, 0, -1};

struct V2 {
    ll x, y;
    V2() {}
    V2(double x, double y) : x(x), y(y) {}
    V2 operator+(V2 v) { return V2(x + v.x, y + v.y); }
    V2 operator-(V2 v) { return V2(x - v.x, y - v.y); }
    V2 operator*(double c) { return V2(c * x, c * y); }
    double dot(V2 v) { return (double)x * v.x + y * v.y; }
    double det(V2 v) { return (double)x * v.y - y * v.x; }
};

ll N, K;
vector<V2> xy;

bool cmp_x(const V2 &v1, const V2 &v2) {
    return (v1.x != v2.x ? v1.x < v2.x : v1.y < v2.y);
}
vector<V2> Graham(vector<V2> vs) {
    sort(All(vs), cmp_x);
    ll k = 0, n = vs.size();
    vector<V2> ws(n * 2);
    REP(i, n) {
        while(k > 1 && (ws[k - 1] - ws[k - 2]).det(vs[i] - ws[k - 1]) <= 0) k--;
        ws[k++] = vs[i];
    }
    for(ll i = n - 2, t = k; i >= 0; i--) {
        while(k > t && (ws[k - 1] - ws[k - 2]).det(vs[i] - ws[k - 1]) <= 0) k--;
        ws[k++] = vs[i];
    }
    ws.resize(k - 1);
    return ws;
}

double dist(V2 v, V2 w) { return (v - w).dot(v - w); }

ll next_combination(ll sub) {
    ll x = sub & -sub, y = sub + x;
    return (((sub & ~y) / x) >> 1LL) | y;
}

signed main() {
    cin >> N >> K;
    REP(i, N) {
        LCIN(X, Y);
        xy.emplace_back(X, Y);
    }
    ll bit = (1LL << K) - 1;
    ll ans = LINF;
    for(; bit < (1LL << N); bit = next_combination(bit)) {
        vector<V2> sel;
        REP(i, N) {
            if(bit & (1LL << i)) {
                sel.emplace_back(xy[i]);
            }
        }
        auto conv = Graham(sel);
        ll x1 = LINF, y1 = LINF, x2 = -LINF, y2 = -LINF;
        REP(i, conv.size()) {
            x1 = min((ll)conv[i].x, x1);
            x2 = max((ll)conv[i].x, x2);
            y1 = min((ll)conv[i].y, y1);
            y2 = max((ll)conv[i].y, y2);
        }
        if((x2 - x1) * (y2 - y1) == 0) continue;
        ans = min((x2 - x1) * (y2 - y1), ans);
    }
    cout << ans << "\n";
}
