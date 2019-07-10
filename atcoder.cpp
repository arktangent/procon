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

//遅延seg
template <typename T, typename E> struct SegmentTree {
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    using P = function<E(E, int)>;
    int n;
    // dat(出力)のマージ（更新）
    F f;
    // lazをdatに反映演算
    G g;
    // laz(更新)のパージ（更新）（下に伝播）
    H h;
    // lazをdatに反映演算(まとめ)
    P p;
    T e1;
    E e2;
    vector<T> dat;
    vector<E> laz;
    SegmentTree(int n_, F f, G g, H h, T e1, E e2, vector<T> v = vector<T>(),
                P p = [](E a, int b) { return a; })
        : f(f), g(g), h(h), e1(e1), e2(e2), p(p) {
        init(n_);
        if(n_ == (int)v.size()) build(n_, v);
    }
    void init(int n_) {
        n = 1;
        while(n < n_) n *= 2;
        dat.clear();
        dat.resize(2 * n - 1, e1);
        laz.clear();
        laz.resize(2 * n - 1, e2);
    }
    void build(int n_, vector<T> v) {
        for(int i = 0; i < n_; i++) dat[i + n - 1] = v[i];
        for(int i = n - 2; i >= 0; i--)
            dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
    }
    inline void eval(int len, int k) {
        if(laz[k] == e2) return;
        if(k * 2 + 1 < n * 2 - 1) {
            laz[k * 2 + 1] = h(laz[k * 2 + 1], laz[k]);
            laz[k * 2 + 2] = h(laz[k * 2 + 2], laz[k]);
        }
        dat[k] = g(dat[k], p(laz[k], len));
        laz[k] = e2;
    }
    T update(int a, int b, E x, int k, int l, int r) {
        eval(r - l, k);
        if(r <= a || b <= l) return dat[k];
        if(a <= l && r <= b) {
            laz[k] = h(laz[k], x);
            return g(dat[k], p(laz[k], r - l));
        }
        eval(r - l, k);
        return dat[k] = f(update(a, b, x, k * 2 + 1, l, (l + r) / 2), update(a, b, x, k * 2 + 2, (l + r) / 2, r));
    }
    T update(int a, int b, E x) { return update(a, b, x, 0, 0, n); }
    T query(int a, int b, int k, int l, int r) {
        eval(r - l, k);
        if(r <= a || b <= l) return e1;
        if(a <= l && r <= b) return dat[k];
        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
    T query(int a, int b) { return query(a, b, 0, 0, n); }
};

signed main() {
    LCIN(n, q);
    ll e1 = 1 << 30, e2 = 0;
    SegmentTree<ll, ll> seg(n, [](ll a, ll b) { return min(a, b); },
                            [](ll a, ll b) { return a + b; },
                            [](ll a, ll b) { return a + b; }, e1, e2, VL(n, e1),
                            [](ll a, ll b) { return a; });
    seg.update(0, n, -e1);
    REP(i, q) {
        if(IN()) {
            LCIN(s, t);
            cout << seg.query(s, t + 1) << "\n";
        } else {
            LCIN(s, t, x);
            seg.update(s, t + 1, x);
        }
    }
}