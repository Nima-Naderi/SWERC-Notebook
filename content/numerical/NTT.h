// NTT exclusively with mod 998244353, easier to type and uses less memory, also allows for quick exponentiation

#include "ModularArithmetic.h"

const ll root = 3; // 62
void ntt(vector<Z> &a) {
    int n = (int)a.size(), L = 31 - __builtin_clz(n);
    static vector<Z> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        Z z[] = {1, Z(root) ^ (mod >> s)};
        for(int i = k ; i < 2 * k ; ++i) rt[i] = rt[i / 2] * z[i & 1];
    }
    vector<int> rev(n);
    for(int i = 0 ; i < n ; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for(int i  = 0 ; i < n ; ++i) if(i < rev[i]) swap(a[i], a[rev[i]]);
    
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) 
            for(int j = 0 ; j < k ; ++j) {
                Z z = rt[j + k] * a[i + j + k], &ai = a[i + j];
                a[i + j + k] = ai - z;
                ai += z;
        }
    }
 
vector<Z> conv(const vector<Z> &a, const vector<Z> &b) {
    if (a.empty() || b.empty()) return {};
    int s = (int)a.size() + (int)b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    Z inv = Z(1)/n;

    vector<Z> L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    for(int i = 0 ; i < n ; ++i)
        out[-i & (n - 1)] = L[i] * R[i] * inv; // also allows exponentiation, after transform just use (A[i] ^ n) * inv
    ntt(out);
    return out;
}
