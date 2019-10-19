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
const ll LINF = 1e18;
// const double PI = atan(1.0) * 4.0;
const ll dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const ll dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
#define PI 3.141592653589793238

// 1000000007 で割ったあまりを扱う構造体
template <int MOD> struct Fp {
    long long val;
    constexpr Fp(long long v = 0) noexcept : val(v % MOD) {
        if(val < 0) v += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator-() const noexcept { return val ? MOD - val : 0; }
    constexpr Fp operator+(const Fp &r) const noexcept {
        return Fp(*this) += r;
    }
    constexpr Fp operator-(const Fp &r) const noexcept {
        return Fp(*this) -= r;
    }
    constexpr Fp operator*(const Fp &r) const noexcept {
        return Fp(*this) *= r;
    }
    constexpr Fp operator/(const Fp &r) const noexcept {
        return Fp(*this) /= r;
    }
    constexpr Fp &operator+=(const Fp &r) noexcept {
        val += r.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Fp &operator-=(const Fp &r) noexcept {
        val -= r.val;
        if(val < 0) val += MOD;
        return *this;
    }
    constexpr Fp &operator*=(const Fp &r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp &operator/=(const Fp &r) noexcept {
        long long a = r.val, b = MOD, u = 1, v = 0;
        while(b) {
            long long t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        val = val * u % MOD;
        if(val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator==(const Fp &r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator!=(const Fp &r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr ostream &operator<<(ostream &os, const Fp<MOD> &x) noexcept {
        return os << x.val;
    }
    friend constexpr istream &operator>>(istream &is, Fp<MOD> &x) noexcept {
        return is >> x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, long long n) noexcept {
        if(n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if(n & 1) t = t * a;
        return t;
    }
};

using mint = Fp<MOD>;

// size用
struct UnionFind {
    vector<ll> par;
    vector<ll> sizes;

    UnionFind(ll n) : par(n), sizes(n, 1) { REP(i, n) par[i] = i; }

    ll find(ll x) {
        if(x == par[x]) return x;
        return par[x] = find(par[x]);
    }

    void unite(ll x, ll y) {
        x = find(x);
        y = find(y);

        if(x == y) return;

        if(sizes[x] < sizes[y]) swap(x, y);

        par[y] = x;
        sizes[x] += sizes[y];
        sizes[y] = 0;
    }

    bool same(ll x, ll y) { return find(x) == find(y); }

    ll size(ll x) { return sizes[find(x)]; }
};

struct edge {
    ll from, to, cost;
    bool operator<(const edge &another) const { return cost < another.cost; };
    bool operator>(const edge &another) const { return cost > another.cost; };
};
vector<edge> es;

ll N, M, X, dist[1010][1010];
bool used[2020];
vector<VPL> G(1010);

ll kruskal() {
    ll res = 0;
    auto uf = UnionFind(N);
    sort(All(es));
    REP(i, SZ(es)) {
        edge e = es[i];
        if(!uf.same(e.from, e.to)) {
            uf.unite(e.from, e.to);
            G[e.from].emplace_back(e.to, e.cost);
            G[e.to].emplace_back(e.from, e.cost);
            used[i] = true;
            res += e.cost;
        }
    }
    return res;
}

void dfs(ll now, ll par, ll root, ll d) {
    dist[root][now] = d;
    FOREACH(e, G[now]) {
        if(e.fi == par) continue;
        dfs(e.fi, now, root, max(d, e.se));
    }
}

signed main() {
    cin >> N >> M >> X;
    REP(i, M) {
        LCIN(u, v, w);
        u--, v--;
        es.push_back({u, v, w});
    }
    Fill(dist, 1LL << 30);
    ll S = kruskal();
    ll D = X - S;
    REP(i, N) dfs(i, -1, i, 0);
    ll large = 0, equal = 0, small = 0;
    REP(i, M) {
        if(used[i]) continue;
        ll u = es[i].from, v = es[i].to;
        ll dif = es[i].cost - dist[u][v];
        if(dif < D)
            small++;
        else if(dif == D)
            equal++;
        else
            large++;
    }
    cout << S << " " << D << "\n";
    cout << small << " " << equal << " " << large << "\n";
    mint ans = 0;
    if(D == 0) {
        ans += (modpow((mint)2, N - 1) - 2) * modpow((mint)2, M - N + 1);
        ans += (modpow((mint)2, equal) - 1) * modpow((mint)2, large) * 2;
    } else if(D > 0) {
        ans += (modpow((mint)2, equal) - 1) * modpow((mint)2, large) * 2;
    }
    cout << ans << "\n";
}
